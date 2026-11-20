#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using namespace std;

// 常量定义
const int INF = 0x3f3f3f3f;
const int HASH_TABLE_SIZE = 31; // 链地址法哈希表桶大小（素数）

// UTF-8 终端显示宽度对齐辅助函数（ASCII 占 1 列，中文 UTF-8 字符占 2 列）
int getDisplayWidth(const string& str) {
    int width = 0;
    size_t i = 0;
    while (i < str.size()) {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if (c < 0x80) {
            width += 1;
            i += 1;
        }
        else if ((c & 0xE0) == 0xC0) {
            width += 2;
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0) {
            width += 2;
            i += 3;
        }
        else {
            width += 2;
            i += 4;
        }
    }
    return width;
}

string padRight(const string& str, int targetWidth) {
    int w = getDisplayWidth(str);
    if (w >= targetWidth) return str + " ";
    return str + string(targetWidth - w, ' ');
}

// ============================================================================
// 1. 数据结构定义与图构建
// ============================================================================

// (1) 地点结点结构体
struct Spot {
    string name;        // 地名
    string description; // 简介
    int popularity;     // 人气度（整数）

    Spot() : name(""), description(""), popularity(0) {}
    Spot(const string& n, const string& d, int p)
        : name(n), description(d), popularity(p) {
    }
};

// (2) 邻接表边结点结构体
struct EdgeNode {
    int adjVex;         // 邻接点在顶点表中的下标
    int weight;         // 路径长度（单位：米）
    EdgeNode* next;     // 指向下一条边的指针

    EdgeNode(int v, int w, EdgeNode* n = nullptr)
        : adjVex(v), weight(w), next(n) {
    }
};

// 邻接表头结点结构体
struct VertexNode {
    Spot data;          // 地点信息
    EdgeNode* firstEdge;// 边表头指针

    VertexNode() : firstEdge(nullptr) {}
    VertexNode(const Spot& s) : data(s), firstEdge(nullptr) {}
};

// ============================================================================
// 4. 关键字快速查找 —— 链地址法哈希表结构设计
// ============================================================================

// 哈希表链表结点
struct HashNode {
    string key;         // 地名关键字
    int vertexIndex;    // 对应图顶点数组的下标
    HashNode* next;     // 链地址法下一个结点指针

    HashNode(const string& k, int idx, HashNode* n = nullptr)
        : key(k), vertexIndex(idx), next(n) {
    }
};

// 链地址法哈希表
struct ChainingHashTable {
    HashNode* buckets[HASH_TABLE_SIZE];

    ChainingHashTable() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            buckets[i] = nullptr;
        }
    }

    // BKDRHash 字符串哈希函数
    int hashFunc(const string& str) const {
        unsigned int seed = 131;
        unsigned int hash = 0;
        for (unsigned char c : str) {
            hash = hash * seed + c;
        }
        return static_cast<int>(hash % HASH_TABLE_SIZE);
    }

    // 清空哈希表
    void clear() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            HashNode* cur = buckets[i];
            while (cur != nullptr) {
                HashNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
            buckets[i] = nullptr;
        }
    }

    // 插入或更新地点索引
    void insert(const string& key, int vertexIndex) {
        int idx = hashFunc(key);
        HashNode* cur = buckets[idx];
        while (cur != nullptr) {
            if (cur->key == key) {
                cur->vertexIndex = vertexIndex;
                return;
            }
            cur = cur->next;
        }
        // 头插法插入到对应哈希桶链表
        buckets[idx] = new HashNode(key, vertexIndex, buckets[idx]);
    }

    // 精确查找地名对应的顶点下标，未找到返回 -1
    int findExact(const string& key) const {
        int idx = hashFunc(key);
        HashNode* cur = buckets[idx];
        while (cur != nullptr) {
            if (cur->key == key) {
                return cur->vertexIndex;
            }
            cur = cur->next;
        }
        return -1;
    }

    ~ChainingHashTable() {
        clear();
    }
};

// 路径查询与排序通用条目结构体
struct PathResultItem {
    Spot spot;              // 终点地点信息
    int distance;           // 距起点最短距离（不可达为 INF）
    vector<string> path;    // 完整路径序列

    PathResultItem() : distance(INF) {}
};

// 最短路径查询返回结构体
struct ShortestPathResult {
    bool found;             // 是否找到有效路径
    string startName;       // 起点名称
    string endName;         // 终点名称
    int totalDistance;      // 总距离
    vector<string> pathSeq; // 路径结点名称序列
    string message;         // 状态说明
};

// ============================================================================
// 校园导航图结构（邻接表 + 链地址法哈希表）
// ============================================================================
class CampusGraph {
private:
    vector<VertexNode> adjList;     // 邻接表顶点数组
    ChainingHashTable spotHash;     // 链地址法哈希表（用于快速查找地点）
    int numVertices;                // 顶点数量
    int numEdges;                   // 无向边数量
    string lastQueryReport;         // 最近一次查询结果缓存（用于导出文件）

    // 内部辅助：释放所有邻接边内存
    void freeEdges() {
        for (size_t i = 0; i < adjList.size(); ++i) {
            EdgeNode* cur = adjList[i].firstEdge;
            while (cur != nullptr) {
                EdgeNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
            adjList[i].firstEdge = nullptr;
        }
    }

    // 内部辅助：在单向邻接链表中插入或更新边
    // 返回值：0=新增成功，1=重复边且更新为更短距离，2=重复边但保留原较短距离
    int insertOrUpdateDirectedEdge(int u, int v, int weight, int& oldWeight) {
        EdgeNode* cur = adjList[u].firstEdge;
        while (cur != nullptr) {
            if (cur->adjVex == v) {
                oldWeight = cur->weight;
                if (weight < cur->weight) {
                    cur->weight = weight;
                    return 1; // 更新为更短路径
                }
                return 2; // 保留原较短或相等路径
            }
            cur = cur->next;
        }
        // 尾插法保持邻接表顺序直观
        EdgeNode* newNode = new EdgeNode(v, weight, nullptr);
        if (adjList[u].firstEdge == nullptr) {
            adjList[u].firstEdge = newNode;
        }
        else {
            EdgeNode* tail = adjList[u].firstEdge;
            while (tail->next != nullptr) {
                tail = tail->next;
            }
            tail->next = newNode;
        }
        return 0;
    }

    // ========================================================================
    // 3.(2) 排序算法实现：快速排序（按距离升序）与归并排序（按人气度降序）
    // ========================================================================

    // 快速排序分区函数（按距离升序；距离相同时按人气度降序）
    int quickSortPartition(vector<PathResultItem>& arr, int low, int high) const {
        PathResultItem pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            bool lessOrEqual = false;
            if (arr[j].distance != pivot.distance) {
                lessOrEqual = (arr[j].distance < pivot.distance);
            }
            else {
                lessOrEqual = (arr[j].spot.popularity >= pivot.spot.popularity);
            }
            if (lessOrEqual) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // 手写快速排序（QuickSort）：按距离升序
    void quickSortByDistance(vector<PathResultItem>& arr, int low, int high) const {
        if (low < high) {
            int pi = quickSortPartition(arr, low, high);
            quickSortByDistance(arr, low, pi - 1);
            quickSortByDistance(arr, pi + 1, high);
        }
    }

    // 归并排序合并函数（按人气度降序；人气度相同时按距离升序）
    void mergeByPopularity(vector<PathResultItem>& arr, int left, int mid, int right) const {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<PathResultItem> L(n1), R(n2);
        for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            bool pickLeft = false;
            if (L[i].spot.popularity != R[j].spot.popularity) {
                pickLeft = (L[i].spot.popularity > R[j].spot.popularity);
            }
            else {
                pickLeft = (L[i].distance <= R[j].distance);
            }
            if (pickLeft) {
                arr[k++] = L[i++];
            }
            else {
                arr[k++] = R[j++];
            }
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    // 手写归并排序（MergeSort）：按人气度降序
    void mergeSortByPopularity(vector<PathResultItem>& arr, int left, int right) const {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortByPopularity(arr, left, mid);
            mergeSortByPopularity(arr, mid + 1, right);
            mergeByPopularity(arr, left, mid, right);
        }
    }

public:
    CampusGraph() : numVertices(0), numEdges(0) {}

    ~CampusGraph() {
        freeEdges();
    }

    // ------------------------------------------------------------------------
    // 1.(2) CreateGraph()：初始化空图
    // ------------------------------------------------------------------------
    void CreateGraph() {
        freeEdges();
        adjList.clear();
        spotHash.clear();
        numVertices = 0;
        numEdges = 0;
    }

    // ------------------------------------------------------------------------
    // 1.(2) AddVertex()：添加地点
    // ------------------------------------------------------------------------
    bool AddVertex(const string& name, const string& description, int popularity, bool verbose = true) {
        if (name.empty()) {
            if (verbose) cout << "  [错误] 地点名称不能为空！" << endl;
            return false;
        }
        if (popularity < 0) {
            if (verbose) cout << "  [错误] 人气度不能为负数！" << endl;
            return false;
        }
        // 通过链地址法哈希表检查是否重名
        int existIdx = spotHash.findExact(name);
        if (existIdx != -1) {
            adjList[existIdx].data.description = description;
            adjList[existIdx].data.popularity = popularity;
            if (verbose) {
                cout << "  [提示] 地点 \"" << name << "\" 已存在，已更新其简介与人气度(" << popularity << ")。" << endl;
            }
            return true;
        }

        Spot newSpot(name, description, popularity);
        adjList.push_back(VertexNode(newSpot));
        int newIdx = numVertices;
        numVertices++;
        spotHash.insert(name, newIdx);

        if (verbose) {
            cout << "  [成功] 已添加地点 [" << newIdx + 1 << "]：" << name
                << " (人气度: " << popularity << "，简介: " << description << ")" << endl;
        }
        return true;
    }

    // ------------------------------------------------------------------------
    // 1.(2) AddEdge()：添加路径（无向图双向添加，含重复路径与异常边界处理）
    // ------------------------------------------------------------------------
    bool AddEdge(const string& startName, const string& endName, int weight, bool verbose = true) {
        if (weight <= 0) {
            if (verbose) {
                cout << "  [边界拦截] 路径长度必须为正整数（输入值: " << weight << "）！" << endl;
            }
            return false;
        }
        if (startName == endName) {
            if (verbose) {
                cout << "  [边界拦截] 起点与终点相同 (\"" << startName << "\")，忽略自环路径！" << endl;
            }
            return false;
        }
        int u = spotHash.findExact(startName);
        int v = spotHash.findExact(endName);
        if (u == -1 || v == -1) {
            if (verbose) {
                cout << "  [边界拦截] 无法添加路径 \"" << startName << " <-> " << endName << "\"：";
                if (u == -1) cout << "起点 \"" << startName << "\" 不存在；";
                if (v == -1) cout << "终点 \"" << endName << "\" 不存在；";
                cout << endl;
            }
            return false;
        }

        int oldWeight = 0;
        int status = insertOrUpdateDirectedEdge(u, v, weight, oldWeight);
        insertOrUpdateDirectedEdge(v, u, weight, oldWeight);

        if (status == 0) {
            numEdges++;
            if (verbose) {
                cout << "  [成功] 已添加双向路径：" << startName << " <---> " << endName
                    << " (距离: " << weight << " 米)" << endl;
            }
        }
        else if (status == 1) {
            if (verbose) {
                cout << "  [边界处理-重复路径] 检测到 \"" << startName << " <---> " << endName
                    << "\" 已存在路径(" << oldWeight << " 米)，新路径(" << weight
                    << " 米)更短，已自动更新为最短边权 " << weight << " 米！" << endl;
            }
        }
        else {
            if (verbose) {
                cout << "  [边界处理-重复路径] 检测到 \"" << startName << " <---> " << endName
                    << "\" 已存在更优路径(" << oldWeight << " 米)，忽略较长/相等的重复路径("
                    << weight << " 米)！" << endl;
            }
        }
        return true;
    }

    // ------------------------------------------------------------------------
    // 2.(1) Dijkstra 算法实现：输入起点地名，计算到所有其他地点的最短路径及距离
    // ------------------------------------------------------------------------
    bool Dijkstra(const string& startName, vector<PathResultItem>& results, bool printOutput = true) {
        results.clear();
        int startIdx = spotHash.findExact(startName);
        if (startIdx == -1) {
            if (printOutput) {
                cout << "  [错误] 未找到起点 \"" << startName << "\"，请先确认地点名称！" << endl;
            }
            return false;
        }

        vector<int> dist(numVertices, INF);
        vector<int> parent(numVertices, -1);
        vector<bool> visited(numVertices, false);

        dist[startIdx] = 0;

        for (int count = 0; count < numVertices; ++count) {
            int u = -1;
            int minDist = INF;
            for (int i = 0; i < numVertices; ++i) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            if (u == -1 || minDist == INF) {
                break; // 剩余顶点均为不可达的孤立节点
            }
            visited[u] = true;

            for (EdgeNode* e = adjList[u].firstEdge; e != nullptr; e = e->next) {
                int v = e->adjVex;
                if (!visited[v] && dist[u] != INF && dist[u] + e->weight < dist[v]) {
                    dist[v] = dist[u] + e->weight;
                    parent[v] = u;
                }
            }
        }

        // 组装所有地点的最短路径结果
        for (int i = 0; i < numVertices; ++i) {
            PathResultItem item;
            item.spot = adjList[i].data;
            item.distance = dist[i];

            if (dist[i] != INF) {
                vector<string> revPath;
                int cur = i;
                while (cur != -1) {
                    revPath.push_back(adjList[cur].data.name);
                    cur = parent[cur];
                }
                reverse(revPath.begin(), revPath.end());
                item.path = revPath;
            }
            results.push_back(item);
        }

        if (printOutput) {
            ostringstream oss;
            oss << "================================================================================\n";
            oss << "  [Dijkstra 单源最短路径查询结果] 起点：" << startName << "\n";
            oss << "================================================================================\n";
            oss << padRight("目标地点", 16)
                << padRight("人气度", 10)
                << padRight("最短距离", 14)
                << "最短路径序列\n";
            oss << "--------------------------------------------------------------------------------\n";

            for (int i = 0; i < numVertices; ++i) {
                if (i == startIdx) continue;
                const PathResultItem& item = results[i];
                oss << padRight(item.spot.name, 16)
                    << padRight(to_string(item.spot.popularity), 10);
                if (item.distance == INF) {
                    oss << padRight("不可达(INF)", 14)
                        << "[孤立地点/无连通路径]\n";
                }
                else {
                    string distStr = to_string(item.distance) + " 米";
                    oss << padRight(distStr, 14);
                    for (size_t k = 0; k < item.path.size(); ++k) {
                        oss << item.path[k];
                        if (k + 1 < item.path.size()) oss << " -> ";
                    }
                    oss << "\n";
                }
            }
            oss << "================================================================================\n";
            cout << oss.str();
            lastQueryReport = oss.str();
        }
        return true;
    }

    // ------------------------------------------------------------------------
    // 2.(2) 路径查询接口：QueryShortestPath(start, end) 返回路径序列和总距离
    // ------------------------------------------------------------------------
    ShortestPathResult QueryShortestPath(const string& startName, const string& endName, bool printOutput = true) {
        ShortestPathResult res;
        res.found = false;
        res.startName = startName;
        res.endName = endName;
        res.totalDistance = INF;

        int u = spotHash.findExact(startName);
        int v = spotHash.findExact(endName);
        if (u == -1 || v == -1) {
            res.message = "起点或终点不存在于校园地图中！";
            if (printOutput) {
                cout << "  [查询失败] " << res.message << endl;
            }
            return res;
        }

        vector<PathResultItem> allResults;
        Dijkstra(startName, allResults, false);

        const PathResultItem& targetItem = allResults[v];
        if (targetItem.distance == INF) {
            res.message = "从 \"" + startName + "\" 到 \"" + endName + "\" 不存在连通路径（孤立地点）！";
            if (printOutput) {
                ostringstream oss;
                oss << "--------------------------------------------------------------------------------\n";
                oss << "  [两点间最短路径查询] " << startName << " ===> " << endName << "\n";
                oss << "  查询结论：" << res.message << "\n";
                oss << "  总距离  ：INF (不可达)\n";
                oss << "--------------------------------------------------------------------------------\n";
                cout << oss.str();
                lastQueryReport = oss.str();
            }
            return res;
        }

        res.found = true;
        res.totalDistance = targetItem.distance;
        res.pathSeq = targetItem.path;
        res.message = "查询成功";

        if (printOutput) {
            ostringstream oss;
            oss << "--------------------------------------------------------------------------------\n";
            oss << "  [两点间最短路径查询] " << startName << " ===> " << endName << "\n";
            oss << "  最短路径序列：";
            for (size_t i = 0; i < res.pathSeq.size(); ++i) {
                oss << res.pathSeq[i];
                if (i + 1 < res.pathSeq.size()) oss << " -> ";
            }
            oss << "\n  最短总距离  ：" << res.totalDistance << " 米\n";
            oss << "  终点简介    ：" << targetItem.spot.description
                << " (人气度: " << targetItem.spot.popularity << ")\n";
            oss << "--------------------------------------------------------------------------------\n";
            cout << oss.str();
            lastQueryReport = oss.str();
        }
        return res;
    }

    // ------------------------------------------------------------------------
    // 3.(1) 景点信息展示：BrowseSpots() 遍历所有地点，输出名称、简介、人气度
    // ------------------------------------------------------------------------
    void BrowseSpots() {
        if (numVertices == 0) {
            cout << "  [提示] 当前校园地图为空，请先添加或导入地点数据！" << endl;
            return;
        }
        ostringstream oss;
        oss << "================================================================================\n";
        oss << "                     校园导航系统 —— 全部景点信息一览表                         \n";
        oss << "   (共 " << numVertices << " 个地点结点，当前有效双向道路 " << numEdges << " 条)\n";
        oss << "================================================================================\n";
        oss << padRight("编号", 6)
            << padRight("地点名称", 16)
            << padRight("人气度", 10)
            << padRight("邻接边数", 10)
            << "地点简介\n";
        oss << "--------------------------------------------------------------------------------\n";

        for (int i = 0; i < numVertices; ++i) {
            int degree = 0;
            for (EdgeNode* e = adjList[i].firstEdge; e != nullptr; e = e->next) {
                degree++;
            }
            oss << padRight(to_string(i + 1), 6)
                << padRight(adjList[i].data.name, 16)
                << padRight(to_string(adjList[i].data.popularity), 10)
                << padRight(to_string(degree), 10)
                << adjList[i].data.description << "\n";
        }
        oss << "================================================================================\n";
        cout << oss.str();
        lastQueryReport = oss.str();
    }

    // ------------------------------------------------------------------------
    // 3.(2) 结果排序功能：
    //   mode = 1 -> 按距离升序（使用快速排序 QuickSort）
    //   mode = 2 -> 按人气度降序（使用归并排序 MergeSort）
    // ------------------------------------------------------------------------
    void SortAndDisplayResults(const string& startName, int sortMode) {
        vector<PathResultItem> items;
        if (!startName.empty() && spotHash.findExact(startName) != -1) {
            Dijkstra(startName, items, false);
        }
        else {
            for (int i = 0; i < numVertices; ++i) {
                PathResultItem item;
                item.spot = adjList[i].data;
                item.distance = 0;
                items.push_back(item);
            }
        }

        if (items.empty()) {
            cout << "  [提示] 暂无可排序的数据！" << endl;
            return;
        }

        ostringstream oss;
        oss << "================================================================================\n";
        if (sortMode == 1) {
            quickSortByDistance(items, 0, static_cast<int>(items.size()) - 1);
            oss << "  [快速排序 QuickSort 结果] 以 \"" << startName << "\" 为起点按最短距离【升序】排列\n";
        }
        else {
            mergeSortByPopularity(items, 0, static_cast<int>(items.size()) - 1);
            oss << "  [归并排序 MergeSort 结果] 校园地点查询结果按人气度【降序】排列";
            if (!startName.empty()) oss << " (参考起点: " << startName << ")";
            oss << "\n";
        }
        oss << "================================================================================\n";
        oss << padRight("排名", 6)
            << padRight("地点名称", 16)
            << padRight("人气度", 10)
            << padRight("距起点距离", 14)
            << "最短路径 / 简介\n";
        oss << "--------------------------------------------------------------------------------\n";

        for (size_t i = 0; i < items.size(); ++i) {
            const PathResultItem& item = items[i];
            string distStr;
            if (startName.empty()) {
                distStr = "-";
            }
            else if (item.distance == INF) {
                distStr = "不可达(INF)";
            }
            else {
                distStr = to_string(item.distance) + " 米";
            }

            oss << padRight(to_string(i + 1), 6)
                << padRight(item.spot.name, 16)
                << padRight(to_string(item.spot.popularity), 10)
                << padRight(distStr, 14);

            if (!startName.empty() && item.distance != INF && item.path.size() > 1) {
                for (size_t k = 0; k < item.path.size(); ++k) {
                    oss << item.path[k];
                    if (k + 1 < item.path.size()) oss << "->";
                }
            }
            else {
                oss << item.spot.description;
            }
            oss << "\n";
        }
        oss << "================================================================================\n";
        cout << oss.str();
        lastQueryReport = oss.str();
    }

    // ------------------------------------------------------------------------
    // 4.(2) 关键字快速查找：SearchSpot(keyword)
    //       基于链地址法哈希表，支持精确哈希匹配与前缀模糊匹配
    // ------------------------------------------------------------------------
    vector<Spot> SearchSpot(const string& keyword, bool printOutput = true) {
        vector<Spot> matchedSpots;
        if (keyword.empty()) {
            if (printOutput) cout << "  [提示] 搜索关键字不能为空！" << endl;
            return matchedSpots;
        }

        vector<bool> added(numVertices, false);
        int exactBucket = -1;

        // 第一步：利用链地址法哈希函数 O(1) 定位精确匹配桶
        int hashIdx = spotHash.hashFunc(keyword);
        for (HashNode* cur = spotHash.buckets[hashIdx]; cur != nullptr; cur = cur->next) {
            if (cur->key == keyword) {
                int vIdx = cur->vertexIndex;
                matchedSpots.push_back(adjList[vIdx].data);
                added[vIdx] = true;
                exactBucket = hashIdx;
                break;
            }
        }

        // 第二步：扫描哈希表各桶链表，执行前缀模糊匹配 (prefix match)
        for (int b = 0; b < HASH_TABLE_SIZE; ++b) {
            for (HashNode* cur = spotHash.buckets[b]; cur != nullptr; cur = cur->next) {
                int vIdx = cur->vertexIndex;
                if (!added[vIdx] && cur->key.find(keyword) == 0) {
                    matchedSpots.push_back(adjList[vIdx].data);
                    added[vIdx] = true;
                }
            }
        }

        // 第三步：补充子串包含匹配（若关键字出现在地名中间也能检索到）
        for (int b = 0; b < HASH_TABLE_SIZE; ++b) {
            for (HashNode* cur = spotHash.buckets[b]; cur != nullptr; cur = cur->next) {
                int vIdx = cur->vertexIndex;
                if (!added[vIdx] && cur->key.find(keyword) != string::npos) {
                    matchedSpots.push_back(adjList[vIdx].data);
                    added[vIdx] = true;
                }
            }
        }

        if (printOutput) {
            ostringstream oss;
            oss << "================================================================================\n";
            oss << "  [链地址法哈希表查找 SearchSpot] 关键字：\"" << keyword
                << "\" (计算哈希桶索引: #" << hashIdx << ")\n";
            oss << "--------------------------------------------------------------------------------\n";
            if (matchedSpots.empty()) {
                oss << "  未找到与关键字 \"" << keyword << "\" 匹配的校园地点。\n";
            }
            else {
                oss << "  共找到 " << matchedSpots.size() << " 个匹配地点";
                if (exactBucket != -1) {
                    oss << "（已在哈希桶 #" << exactBucket << " 中直接命中精确匹配项）";
                }
                oss << "：\n";
                oss << padRight("序号", 6)
                    << padRight("地点名称", 16)
                    << padRight("哈希桶号", 12)
                    << padRight("人气度", 10)
                    << "地点简介\n";
                oss << "--------------------------------------------------------------------------------\n";
                for (size_t i = 0; i < matchedSpots.size(); ++i) {
                    int bIdx = spotHash.hashFunc(matchedSpots[i].name);
                    oss << padRight(to_string(i + 1), 6)
                        << padRight(matchedSpots[i].name, 16)
                        << padRight("Bucket#" + to_string(bIdx), 12)
                        << padRight(to_string(matchedSpots[i].popularity), 10)
                        << matchedSpots[i].description << "\n";
                }
            }
            oss << "================================================================================\n";
            cout << oss.str();
            lastQueryReport = oss.str();
        }
        return matchedSpots;
    }

    // 展示链地址法哈希表内部存储分布（用于验证哈希表结构）
    void DisplayHashTableStructure() const {
        cout << "--------------------------------------------------------------------------------\n";
        cout << "  [链地址法哈希表内部桶结构展示] (表长 HASH_TABLE_SIZE = " << HASH_TABLE_SIZE << ")\n";
        cout << "--------------------------------------------------------------------------------\n";
        int usedBuckets = 0;
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            if (spotHash.buckets[i] != nullptr) {
                usedBuckets++;
                cout << "  Bucket[" << setw(2) << i << "] -> ";
                HashNode* cur = spotHash.buckets[i];
                while (cur != nullptr) {
                    cout << "[" << cur->key << " (顶点#" << cur->vertexIndex + 1 << ")]";
                    if (cur->next != nullptr) cout << " --> ";
                    cur = cur->next;
                }
                cout << " --> NULL\n";
            }
        }
        cout << "  非空哈希桶数：" << usedBuckets << " / " << HASH_TABLE_SIZE
            << "，装填因子 alpha = " << fixed << setprecision(2)
            << (static_cast<double>(numVertices) / HASH_TABLE_SIZE) << "\n";
        cout << "--------------------------------------------------------------------------------\n";
    }

    // ------------------------------------------------------------------------
    // 5.(2) 扩展功能：从文件导入校园地图数据（地点、路径）
    // ------------------------------------------------------------------------
    bool ImportFromFile(const string& filename, bool resetBeforeImport = true) {
        ifstream fin(filename.c_str());
        if (!fin.is_open()) {
            cout << "  [错误] 无法打开地图数据文件：" << filename << endl;
            return false;
        }

        if (resetBeforeImport) {
            CreateGraph();
        }

        cout << "\n>>> 正在从文件 \"" << filename << "\" 导入校园地图数据..." << endl;
        string line;
        int section = 0; // 1: VERTICES, 2: EDGES
        int vCount = 0, eCount = 0;

        while (getline(fin, line)) {
            while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t')) {
                line.pop_back();
            }
            size_t firstPos = line.find_first_not_of(" \t");
            if (firstPos == string::npos) continue;
            line = line.substr(firstPos);

            if (line.empty() || line[0] == '#') continue;

            if (line == "[VERTICES]") {
                section = 1;
                continue;
            }
            else if (line == "[EDGES]") {
                section = 2;
                continue;
            }

            if (section == 1) {
                stringstream ss(line);
                string name, desc, popStr;
                if (getline(ss, name, '|') && getline(ss, desc, '|') && getline(ss, popStr)) {
                    int pop = stoi(popStr);
                    if (AddVertex(name, desc, pop, true)) {
                        vCount++;
                    }
                }
            }
            else if (section == 2) {
                stringstream ss(line);
                string uName, vName, wStr;
                if (getline(ss, uName, '|') && getline(ss, vName, '|') && getline(ss, wStr)) {
                    int w = stoi(wStr);
                    if (AddEdge(uName, vName, w, true)) {
                        eCount++;
                    }
                }
            }
        }
        fin.close();
        cout << ">>> 文件导入完成：共处理地点记录 " << vCount << " 条，路径记录 " << eCount
            << " 条（当前有效顶点数: " << numVertices << "，有效无向边数: " << numEdges << "）。\n" << endl;
        return true;
    }

    // ------------------------------------------------------------------------
    // 5.(2) 扩展功能：导出查询结果到文件
    // ------------------------------------------------------------------------
    bool ExportResultToFile(const string& filename, const string& content = "", bool appendMode = true) {
        string textToSave = content.empty() ? lastQueryReport : content;
        if (textToSave.empty()) {
            cout << "  [提示] 当前暂无可导出的查询结果，请先执行一次路径查询、景点排序或关键字查找！" << endl;
            return false;
        }

        ofstream fout(filename.c_str(), appendMode ? (ios::out | ios::app) : ios::out);
        if (!fout.is_open()) {
            cout << "  [错误] 无法写入目标文件：" << filename << endl;
            return false;
        }

        fout << textToSave << "\n";
        fout.close();
        cout << "  [导出成功] 查询结果已保存至文件：\"" << filename << "\" ("
            << (appendMode ? "追加模式" : "覆盖模式") << ")" << endl;
        return true;
    }

    int getVertexCount() const { return numVertices; }
    int getEdgeCount() const { return numEdges; }
    string getLastQueryReport() const { return lastQueryReport; }
};

// ============================================================================
// 交互辅助函数：查询后询问是否立即导出结果（兼顾交互提示与菜单导出）
// ============================================================================
void PromptImmediateExport(CampusGraph& graph, const string& defaultExportFile) {
    cout << "  是否将本次查询结果立即导出到文件 \"" << defaultExportFile << "\"？(y/n，默认 n): ";
    string ans;
    getline(cin, ans);
    if (!ans.empty() && (ans[0] == 'y' || ans[0] == 'Y')) {
        graph.ExportResultToFile(defaultExportFile, "", true);
    }
}

// ============================================================================
// 5.(3) 自动化测试与验证套件（正常场景 + 边界场景完整运行并导出）
// ============================================================================
void RunAutomatedTestSuite(const string& mapFile, const string& exportFile) {
    cout << "================================================================================\n";
    cout << "          专题三：图的应用与系统集成 —— 校园导航系统自动化测试套件              \n";
    cout << "================================================================================\n";

    CampusGraph graph;
    {
        ofstream clearOut(exportFile.c_str(), ios::out);
        clearOut << "================================================================================\n";
        clearOut << "                 校园导航系统 —— 查询与测试结果导出报告                         \n";
        clearOut << "================================================================================\n\n";
    }

    // 测试1：从文件导入校园地图数据（含重复路径与孤立地点）
    cout << "\n【测试用例 1】图结构初始化与地图文件导入（含重复路径边界验证）\n";
    cout << "--------------------------------------------------------------------------------\n";
    graph.CreateGraph();
    graph.ImportFromFile(mapFile, false);

    // 测试2：异常与边界路径拦截测试
    cout << "【测试用例 2】异常与边界路径拦截测试（不存在地点、自环路径、非正距离）\n";
    cout << "--------------------------------------------------------------------------------\n";
    graph.AddEdge("学校南门", "学校南门", 100, true);
    graph.AddEdge("学校南门", "未建成的体育中心", 250, true);
    graph.AddEdge("图书馆", "第一食堂", -50, true);

    // 测试3：浏览所有景点信息
    cout << "\n【测试用例 3】景点信息浏览 BrowseSpots()\n";
    cout << "--------------------------------------------------------------------------------\n";
    graph.BrowseSpots();
    graph.ExportResultToFile(exportFile, "", true);

    // 测试4：Dijkstra 单源最短路径查询（验证多路径最优解与孤立地点“天文观测台”）
    cout << "\n【测试用例 4】Dijkstra 单源最短路径查询（起点：学校南门，含孤立地点边界验证）\n";
    cout << "--------------------------------------------------------------------------------\n";
    vector<PathResultItem> dijkstraRes;
    graph.Dijkstra("学校南门", dijkstraRes, true);
    graph.ExportResultToFile(exportFile, "", true);

    // 测试5：指定起终点最短路径接口 QueryShortestPath(start, end)
    cout << "\n【测试用例 5】指定起终点最短路径查询 QueryShortestPath(start, end)\n";
    cout << "--------------------------------------------------------------------------------\n";
    graph.QueryShortestPath("学校南门", "综合体育馆", true);
    graph.ExportResultToFile(exportFile, "", true);

    graph.QueryShortestPath("学校南门", "图书馆", true);
    graph.ExportResultToFile(exportFile, "", true);

    graph.QueryShortestPath("教学主楼", "实验东楼", true);
    graph.ExportResultToFile(exportFile, "", true);

    graph.QueryShortestPath("学校南门", "天文观测台", true);
    graph.ExportResultToFile(exportFile, "", true);

    // 测试6：结果排序功能验证（快速排序按距离升序 + 归并排序按人气度降序）
    cout << "\n【测试用例 6】结果排序功能验证（快速排序按距离升序 & 归并排序按人气度降序）\n";
    cout << "--------------------------------------------------------------------------------\n";
    graph.SortAndDisplayResults("学校南门", 1); // 快速排序：按距离升序
    graph.ExportResultToFile(exportFile, "", true);

    graph.SortAndDisplayResults("学校南门", 2); // 归并排序：按人气度降序
    graph.ExportResultToFile(exportFile, "", true);

    // 测试7：链地址法哈希表结构与关键字快速查找（精确匹配 + 前缀模糊匹配）
    cout << "\n【测试用例 7】链地址法哈希表与关键字快速查找 SearchSpot(keyword)\n";
    cout << "--------------------------------------------------------------------------------\n";
    graph.DisplayHashTableStructure();
    graph.SearchSpot("教学", true);
    graph.ExportResultToFile(exportFile, "", true);

    graph.SearchSpot("实验", true);
    graph.ExportResultToFile(exportFile, "", true);

    graph.SearchSpot("图书馆", true);
    graph.ExportResultToFile(exportFile, "", true);

    graph.SearchSpot("游泳馆北门", true);
    graph.ExportResultToFile(exportFile, "", true);

    cout << "\n================================================================================\n";
    cout << "  全部自动化测试用例执行完毕！所有查询与验证结果已同步导出至：" << exportFile << "\n";
    cout << "================================================================================\n";
}

// ============================================================================
// 打印命令行交互主菜单
// ============================================================================
void PrintMenu() {
    cout << "\n============================================================\n";
    cout << "           校园导航系统 (图的应用与系统集成)                \n";
    cout << "============================================================\n";
    cout << "  1. 添加地点 (AddVertex)\n";
    cout << "  2. 添加路径 (AddEdge)\n";
    cout << "  3. 查询最短路径 (Dijkstra / QueryShortestPath)\n";
    cout << "  4. 浏览景点（排序）(BrowseSpots / 快速排序 & 归并排序)\n";
    cout << "  5. 关键字查找 (SearchSpot 链地址法哈希表前缀模糊匹配)\n";
    cout << "  6. 退出\n";
    cout << "------------------------------------------------------------\n";
    cout << "  [扩展与测试功能]\n";
    cout << "  7. 从文件导入校园地图数据\n";
    cout << "  8. 导出最近一次查询结果到文件\n";
    cout << "  9. 一键运行全场景测试用例并生成测试结果文件\n";
    cout << "============================================================\n";
    cout << "请选择操作编号 (1-9): ";
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    // Visual Studio / Windows 控制台 UTF-8 编码支持，防止中文乱码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    string defaultMapFile = "campus_map.txt";
    string defaultExportFile = "query_results.txt";

    // 若携带命令行参数 --test，则直接运行自动化全场景测试套件
    if (argc > 1 && string(argv[1]) == "--test") {
        if (argc > 2) defaultMapFile = argv[2];
        if (argc > 3) defaultExportFile = argv[3];
        RunAutomatedTestSuite(defaultMapFile, defaultExportFile);
        return 0;
    }

    CampusGraph campus;
    campus.CreateGraph();

    cout << "============================================================\n";
    cout << "         欢迎使用校园导航系统 (Visual Studio C++ 版)        \n";
    cout << "============================================================\n";

    // 启动时检测默认地图数据文件，支持一键自动加载
    ifstream checkFile(defaultMapFile.c_str());
    if (checkFile.is_open()) {
        checkFile.close();
        cout << "检测到默认校园地图数据文件 \"" << defaultMapFile << "\"，是否立即导入？(y/n，默认 y): ";
        string initChoice;
        if (getline(cin, initChoice)) {
            if (initChoice.empty() || initChoice[0] == 'y' || initChoice[0] == 'Y') {
                campus.ImportFromFile(defaultMapFile, true);
            }
        }
    }

    while (true) {
        PrintMenu();
        string choiceStr;
        if (!getline(cin, choiceStr)) break;
        if (choiceStr.empty()) continue;

        int choice = 0;
        try {
            choice = stoi(choiceStr);
        }
        catch (...) {
            cout << "  [提示] 无效输入，请输入数字 1 ~ 9！" << endl;
            continue;
        }

        if (choice == 1) {
            string name, desc, popStr;
            cout << "  请输入地点名称: ";
            getline(cin, name);
            cout << "  请输入地点简介: ";
            getline(cin, desc);
            cout << "  请输入地点人气度(整数，如 0-100): ";
            getline(cin, popStr);
            int pop = 0;
            try {
                pop = stoi(popStr);
            }
            catch (...) {
                cout << "  [错误] 人气度输入格式有误！" << endl;
                continue;
            }
            campus.AddVertex(name, desc, pop, true);

        }
        else if (choice == 2) {
            string uName, vName, wStr;
            cout << "  请输入起点地名: ";
            getline(cin, uName);
            cout << "  请输入终点地名: ";
            getline(cin, vName);
            cout << "  请输入路径长度(正整数，单位：米): ";
            getline(cin, wStr);
            int w = 0;
            try {
                w = stoi(wStr);
            }
            catch (...) {
                cout << "  [错误] 路径长度输入格式有误！" << endl;
                continue;
            }
            campus.AddEdge(uName, vName, w, true);

        }
        else if (choice == 3) {
            cout << "  请选择查询模式：[1] 查询两点间最短路径 (QueryShortestPath)  [2] 查询起点到所有地点的最短路径 (Dijkstra): ";
            string subMode;
            getline(cin, subMode);
            if (subMode == "2") {
                string startName;
                cout << "  请输入起点地名: ";
                getline(cin, startName);
                vector<PathResultItem> results;
                if (campus.Dijkstra(startName, results, true)) {
                    PromptImmediateExport(campus, defaultExportFile);
                }
            }
            else {
                string startName, endName;
                cout << "  请输入起点地名: ";
                getline(cin, startName);
                cout << "  请输入终点地名: ";
                getline(cin, endName);
                campus.QueryShortestPath(startName, endName, true);
                PromptImmediateExport(campus, defaultExportFile);
            }

        }
        else if (choice == 4) {
            campus.BrowseSpots();
            if (campus.getVertexCount() == 0) continue;

            cout << "\n  请选择结果排序方式：\n";
            cout << "    [1] 按距离升序排序（使用快速排序 QuickSort）\n";
            cout << "    [2] 按人气度降序排序（使用归并排序 MergeSort）\n";
            cout << "    [0] 仅浏览不额外排序\n";
            cout << "  请输入选项 (0-2): ";
            string sortOpt;
            getline(cin, sortOpt);
            if (sortOpt == "1") {
                string startName;
                cout << "  请输入计算距离的参考起点地名（如 学校南门）: ";
                getline(cin, startName);
                campus.SortAndDisplayResults(startName, 1);
                PromptImmediateExport(campus, defaultExportFile);
            }
            else if (sortOpt == "2") {
                string startName;
                cout << "  请输入可选的参考起点地名（直接回车则仅按人气度降序展示）: ";
                getline(cin, startName);
                campus.SortAndDisplayResults(startName, 2);
                PromptImmediateExport(campus, defaultExportFile);
            }
            else {
                PromptImmediateExport(campus, defaultExportFile);
            }

        }
        else if (choice == 5) {
            string keyword;
            cout << "  请输入地名关键字（支持精确查找与前缀模糊匹配，如“教学”、“实验”）: ";
            getline(cin, keyword);
            campus.SearchSpot(keyword, true);
            PromptImmediateExport(campus, defaultExportFile);

        }
        else if (choice == 6) {
            cout << "  感谢使用校园导航系统，再见！" << endl;
            break;

        }
        else if (choice == 7) {
            string filename;
            cout << "  请输入要导入的地图文件路径（直接回车默认 \"" << defaultMapFile << "\"）: ";
            getline(cin, filename);
            if (filename.empty()) filename = defaultMapFile;
            campus.ImportFromFile(filename, true);

        }
        else if (choice == 8) {
            string filename;
            cout << "  请输入导出结果文件路径（直接回车默认 \"" << defaultExportFile << "\"）: ";
            getline(cin, filename);
            if (filename.empty()) filename = defaultExportFile;
            campus.ExportResultToFile(filename, "", true);

        }
        else if (choice == 9) {
            RunAutomatedTestSuite(defaultMapFile, defaultExportFile);
        }
        else {
            cout << "  [提示] 无效的菜单编号，请输入 1 ~ 9！" << endl;
        }
    }

    return 0;
}