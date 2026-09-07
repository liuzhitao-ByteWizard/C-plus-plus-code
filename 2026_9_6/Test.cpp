#include "Date.h"

#include <climits>
#include <exception>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

/*
 * 本文件使用一个很小的自建测试器，而不使用 assert。
 *
 * 原因是 Visual Studio 的 Release 配置会定义 NDEBUG，此时 assert 中的
 * 判断会被编译器完全删除。下面的测试器在 Debug 和 Release 中都会执行，
 * 会逐项打印结果、统计失败数，并通过 main 的返回值告诉操作系统测试是否通过。
 */

// 极端日期向量按照当前 Visual Studio 工程的 32 位 int 计算。
// 把前提写成编译期检查，可以防止代码换到不同整数模型后仍使用错误的期望值。
static_assert(INT_MAX == 2147483647, "These tests require a 32-bit int.");
static_assert(INT_MIN == (-2147483647 - 1), "These tests require a 32-bit int.");

// 这些编译期检查用于固定 Date 的公开接口。
// 它们无需运行，只要某个函数缺少 const、返回类型不正确或输出不能链式调用，
// 编译就会立刻失败。
static_assert(std::is_same<
	decltype(std::declval<const Date&>() + 1), Date>::value,
	"Date::operator+ must be callable on const Date and return Date.");
static_assert(std::is_same<
	decltype(std::declval<const Date&>() - 1), Date>::value,
	"Date::operator-(int) must be callable on const Date and return Date.");
static_assert(std::is_same<
	decltype(std::declval<const Date&>() - std::declval<const Date&>()), int>::value,
	"Date::operator-(Date) must return int.");
static_assert(std::is_same<
	decltype(std::declval<const Date&>().Print()), void>::value,
	"Date::Print must be callable on const Date.");
static_assert(std::is_same<
	decltype(std::declval<Date&>() += 1), Date&>::value,
	"Date::operator+= must return Date&.");
static_assert(std::is_same<
	decltype(std::declval<Date&>() -= 1), Date&>::value,
	"Date::operator-= must return Date&.");
static_assert(std::is_same<
	decltype(++std::declval<Date&>()), Date&>::value,
	"Prefix ++ must return Date&.");
static_assert(std::is_same<
	decltype(std::declval<Date&>()++), Date>::value,
	"Postfix ++ must return Date.");
static_assert(std::is_same<
	decltype(--std::declval<Date&>()), Date&>::value,
	"Prefix -- must return Date&.");
static_assert(std::is_same<
	decltype(std::declval<Date&>()--), Date>::value,
	"Postfix -- must return Date.");
static_assert(std::is_same<
	decltype(std::declval<std::ostream&>() << std::declval<const Date&>()),
	std::ostream&>::value,
	"Date stream output must return ostream&.");

static_assert(noexcept(std::declval<const Date&>() > std::declval<const Date&>()),
	"Date::operator> must be noexcept.");
static_assert(noexcept(std::declval<const Date&>() >= std::declval<const Date&>()),
	"Date::operator>= must be noexcept.");
static_assert(noexcept(std::declval<const Date&>() < std::declval<const Date&>()),
	"Date::operator< must be noexcept.");
static_assert(noexcept(std::declval<const Date&>() <= std::declval<const Date&>()),
	"Date::operator<= must be noexcept.");
static_assert(noexcept(std::declval<const Date&>() == std::declval<const Date&>()),
	"Date::operator== must be noexcept.");
static_assert(noexcept(std::declval<const Date&>() != std::declval<const Date&>()),
	"Date::operator!= must be noexcept.");

class TestRunner
{
public:
	void Check(bool condition, const std::string& name,
		const std::string& details = std::string())
	{
		if (condition)
		{
			++_passed;
			std::cout << "[PASS] " << name << '\n';
			return;
		}

		RecordFailure(name, details);
	}

	void RecordFailure(const std::string& name,
		const std::string& details = std::string())
	{
		++_failed;
		std::cout << "[FAIL] " << name;
		if (!details.empty())
		{
			std::cout << " -- " << details;
		}
		std::cout << '\n';
	}

	/*
	 * 异常测试不仅检查“是否抛异常”，还检查异常类别。
	 * 三类异常各有明确职责：
	 *   invalid_argument：传给构造函数的日期本身非法；
	 *   out_of_range：合法日期经过加减后越过 Date 支持的范围；
	 *   overflow_error：两个合法日期的天数差无法放进 int。
	 */
	template<class ExpectedException, class Callable>
	void ExpectThrows(Callable callable, const std::string& name)
	{
		try
		{
			callable();
		}
		catch (const ExpectedException&)
		{
			++_passed;
			std::cout << "[PASS] " << name << '\n';
			return;
		}
		catch (const std::exception& error)
		{
			RecordFailure(name,
				std::string("抛出了其他标准异常：") + error.what());
			return;
		}
		catch (...)
		{
			RecordFailure(name, "抛出了非标准异常");
			return;
		}

		RecordFailure(name, "没有抛出预期异常");
	}

	int FailedCount() const
	{
		return _failed;
	}

	void PrintSummary() const
	{
		std::cout << "\n========== 测试汇总 ==========\n"
			<< "通过：" << _passed << '\n'
			<< "失败：" << _failed << '\n'
			<< "总计：" << (_passed + _failed) << '\n';
	}

private:
	int _passed = 0;
	int _failed = 0;
};

// Date 没有暴露 getter，因此测试通过公开的 == 比较结果。
// 失败时再利用 operator<< 打印实际日期和期望日期，便于快速定位问题。
void CheckDate(TestRunner& runner, const Date& actual,
	const Date& expected, const std::string& name)
{
	if (actual == expected)
	{
		runner.Check(true, name);
		return;
	}

	std::ostringstream details;
	details << "期望 " << expected << "，实际 " << actual;
	runner.Check(false, name, details.str());
}

void CheckInteger(TestRunner& runner, int actual,
	int expected, const std::string& name)
{
	if (actual == expected)
	{
		runner.Check(true, name);
		return;
	}

	std::ostringstream details;
	details << "期望 " << expected << "，实际 " << actual;
	runner.Check(false, name, details.str());
}

/*
 * 一对严格有序的日期可以同时验证六个比较运算符的正向和反向关系。
 * 这样能发现某个派生运算符（例如 <= 或 >=）只在相等场景正确的问题。
 */
void CheckStrictOrder(TestRunner& runner, const Date& earlier,
	const Date& later, const std::string& name)
{
	const bool correct =
		earlier < later
		&& earlier <= later
		&& !(earlier > later)
		&& !(earlier >= later)
		&& earlier != later
		&& !(earlier == later)
		&& later > earlier
		&& later >= earlier
		&& !(later < earlier)
		&& !(later <= earlier)
		&& later != earlier
		&& !(later == earlier);

	runner.Check(correct, name);
}

/*
 * Print() 固定写入 std::cout。这个 RAII 辅助器临时把 cout 重定向到字符串，
 * 并在离开作用域时自动恢复；即使后续测试逻辑发生异常，也不会破坏控制台输出。
 */
class CoutCapture
{
public:
	CoutCapture()
		: _original(std::cout.rdbuf(_captured.rdbuf()))
	{
	}

	~CoutCapture()
	{
		std::cout.rdbuf(_original);
	}

	CoutCapture(const CoutCapture&) = delete;
	CoutCapture& operator=(const CoutCapture&) = delete;

	std::string Text() const
	{
		return _captured.str();
	}

private:
	// 成员按声明顺序构造，因此字符串流会先于 _original 初始化。
	std::ostringstream _captured;
	std::streambuf* _original;
};

typedef void (*TestGroup)(TestRunner&);

// 每个测试组外层再捕获一次意外异常，避免一个实现错误阻止后续测试组执行。
void RunGroup(TestRunner& runner, const std::string& name, TestGroup group)
{
	std::cout << "\n========== " << name << " ==========\n";
	try
	{
		group(runner);
	}
	catch (const std::exception& error)
	{
		runner.RecordFailure(name + " 出现未处理异常", error.what());
	}
	catch (...)
	{
		runner.RecordFailure(name + " 出现未处理异常", "非标准异常");
	}
}

void TestConstructionAndValidation(TestRunner& runner)
{
	/*
	 * 先确认合法边界：默认日期等于 1/1/1，最大 int 年份也能构造。
	 * 1900 能被 100 整除但不能被 400 整除，所以不是闰年；
	 * 2000 能被 400 整除，所以 2 月 29 日合法。
	 */
	CheckDate(runner, Date(), Date(1, 1, 1), "默认构造得到最小日期");
	CheckDate(runner, Date(INT_MAX, 12, 31), Date(INT_MAX, 12, 31),
		"最大年份的最后一天可以构造");
	CheckDate(runner, Date(2000, 2, 29), Date(2000, 2, 29),
		"2000 年闰日合法");
	CheckDate(runner, Date(2024, 2, 29), Date(2024, 2, 29),
		"2024 年闰日合法");

	// 年份必须从 1 开始；INT_MIN 也应在做任何日期计算前被安全拒绝。
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(INT_MIN, 1, 1); }, "INT_MIN 年份被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(-1, 1, 1); }, "负年份被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(0, 1, 1); }, "年份 0 被拒绝");

	/*
	 * 极端月份用于确认实现先检查月份范围，再访问月份天数表。
	 * 如果顺序相反，month - 1 会导致数组越界，而不是稳定地抛出异常。
	 */
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, INT_MIN, 1); }, "INT_MIN 月份被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, 0, 1); }, "月份 0 被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, 13, 1); }, "月份 13 被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, INT_MAX, 1); }, "INT_MAX 月份被拒绝");

	// 日期既不能小于 1，也不能超过对应月份在该年份的实际天数。
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, 1, INT_MIN); }, "INT_MIN 日被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, 1, 0); }, "日期 0 被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, 1, INT_MAX); }, "INT_MAX 日被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2023, 2, 29); }, "普通年的 2 月 29 日被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(1900, 2, 29); }, "世纪普通年的闰日被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, 2, 30); }, "闰年 2 月 30 日被拒绝");
	runner.ExpectThrows<std::invalid_argument>(
		[] { (void)Date(2024, 4, 31); }, "小月的第 31 天被拒绝");
}

void TestOutput(TestRunner& runner)
{
	const Date date(2024, 2, 9);

	/*
	 * 插入运算符只负责写入日期，不擅自换行；返回原流后，
	 * 调用方才能继续追加字符或其他日期。
	 */
	std::ostringstream output;
	std::ostream& returned = (output << date);
	runner.Check(&returned == &output, "operator<< 返回传入的同一个流");
	runner.Check(output.str() == "2024/2/9",
		"operator<< 使用年/月/日格式且不换行", output.str());

	std::ostringstream chained;
	chained << '[' << date << ']' << ' ' << Date(2025, 12, 31);
	runner.Check(chained.str() == "[2024/2/9] 2025/12/31",
		"operator<< 支持链式输出", chained.str());

	// Print() 是便捷显示函数，因此与 operator<< 不同，它应主动补一个换行。
	std::string printText;
	{
		CoutCapture capture;
		date.Print();
		printText = capture.Text();
	}
	runner.Check(printText == "2024/2/9\n",
		"const Date::Print 输出日期并换行", printText);
}

void TestComparisons(TestRunner& runner)
{
	const Date left(2024, 6, 15);
	const Date right(2024, 6, 15);

	// 相等场景专门验证 <= 和 >= 必须同时为真，而 < 和 > 必须同时为假。
	const bool equalRelations =
		left == right
		&& !(left != right)
		&& !(left < right)
		&& left <= right
		&& !(left > right)
		&& left >= right;
	runner.Check(equalRelations, "相等日期的六个比较结果正确");

	CheckStrictOrder(runner, Date(2024, 6, 14), Date(2024, 6, 15),
		"仅日期不同的顺序正确");
	CheckStrictOrder(runner, Date(2024, 5, 31), Date(2024, 6, 1),
		"跨月份的顺序正确");
	CheckStrictOrder(runner, Date(2023, 12, 31), Date(2024, 1, 1),
		"跨年份的顺序正确");
	CheckStrictOrder(runner, Date(1, 1, 1), Date(INT_MAX, 12, 31),
		"最小日期与最大日期的顺序正确");
}

void TestOrdinaryArithmetic(TestRunner& runner)
{
	/*
	 * 这一组覆盖月底、年底以及闰年二月。1900 和 2000 可以发现
	 * 只检查“能被 4 整除”而遗漏世纪年规则的错误。
	 */
	CheckDate(runner, Date(2024, 2, 28) + 1, Date(2024, 2, 29),
		"闰年 2 月 28 日加一天");
	CheckDate(runner, Date(2024, 2, 28) + 2, Date(2024, 3, 1),
		"闰年跨过 2 月 29 日");
	CheckDate(runner, Date(2023, 2, 28) + 1, Date(2023, 3, 1),
		"普通年二月底加一天");
	CheckDate(runner, Date(1900, 2, 28) + 1, Date(1900, 3, 1),
		"1900 世纪普通年二月底加一天");
	CheckDate(runner, Date(2000, 2, 28) + 1, Date(2000, 2, 29),
		"2000 世纪闰年二月底加一天");
	CheckDate(runner, Date(2023, 12, 31) + 1, Date(2024, 1, 1),
		"年末加一天");

	/*
	 * 日期序号的反向换算以 400 年（146097 天）为一个周期，
	 * 再拆成世纪、四年和单年子周期。各级周期的最后一天与下一周期第一天
	 * 最容易出现“多一年/少一天”，因此用精确偏移固定这些边界。
	 */
	CheckDate(runner, Date(1, 1, 1) + 1460, Date(4, 12, 31),
		"第一个四年周期的最后一天");
	CheckDate(runner, Date(1, 1, 1) + 1461, Date(5, 1, 1),
		"完整四年周期后的第一天");
	CheckDate(runner, Date(1, 1, 1) + 36523, Date(100, 12, 31),
		"第一个世纪周期的最后一天");
	CheckDate(runner, Date(1, 1, 1) + 36524, Date(101, 1, 1),
		"世纪普通年周期后的第一天");
	CheckDate(runner, Date(1, 1, 1) + 146096, Date(400, 12, 31),
		"第一个 400 年周期的最后一天");
	CheckDate(runner, Date(1, 1, 1) + 146097, Date(401, 1, 1),
		"完整 400 年周期后的第一天");
	CheckDate(runner, Date(401, 1, 1) - 146097, Date(1, 1, 1),
		"完整 400 年周期可以反向恢复");

	CheckDate(runner, Date(2024, 3, 1) - 1, Date(2024, 2, 29),
		"闰年三月一日减一天");
	CheckDate(runner, Date(2023, 3, 1) - 1, Date(2023, 2, 28),
		"普通年三月一日减一天");
	CheckDate(runner, Date(2024, 1, 1) - 1, Date(2023, 12, 31),
		"年初减一天");

	// 零偏移和负偏移用于确认 + 与 - 的语义在两个方向上保持一致。
	const Date source(2024, 3, 1);
	CheckDate(runner, source + 0, source, "加零保持日期不变");
	CheckDate(runner, source - 0, source, "减零保持日期不变");
	CheckDate(runner, source + (-1), Date(2024, 2, 29),
		"加负数等价于向前移动");
	CheckDate(runner, Date(2024, 2, 28) - (-2), Date(2024, 3, 1),
		"减负数等价于向后移动");
	CheckDate(runner, source, Date(2024, 3, 1),
		"非修改型加减不会改变 const 源对象");

	// 复合赋值既要修改对象，也必须返回这个对象本身的引用。
	Date plusAssign(2023, 12, 31);
	Date& plusReference = (plusAssign += 1);
	runner.Check(&plusReference == &plusAssign, "operator+= 返回原对象引用");
	CheckDate(runner, plusAssign, Date(2024, 1, 1), "operator+= 修改日期");

	Date minusAssign(2024, 3, 1);
	Date& minusReference = (minusAssign -= 1);
	runner.Check(&minusReference == &minusAssign, "operator-= 返回原对象引用");
	CheckDate(runner, minusAssign, Date(2024, 2, 29), "operator-= 修改日期");
}

void TestIncrementAndDecrement(TestRunner& runner)
{
	/*
	 * 前置版本应返回修改后的原对象引用；后置版本应返回修改前的副本。
	 * 用闰日、月界和年界可以同时验证返回值语义与日期进位/借位。
	 */
	Date prefixIncrement(2024, 2, 28);
	Date& incrementReference = ++prefixIncrement;
	runner.Check(&incrementReference == &prefixIncrement, "前置 ++ 返回原对象引用");
	CheckDate(runner, prefixIncrement, Date(2024, 2, 29),
		"前置 ++ 得到闰日");

	Date postfixIncrement(2024, 2, 29);
	const Date incrementOldValue = postfixIncrement++;
	CheckDate(runner, incrementOldValue, Date(2024, 2, 29),
		"后置 ++ 返回旧日期");
	CheckDate(runner, postfixIncrement, Date(2024, 3, 1),
		"后置 ++ 修改为下一天");

	Date prefixDecrement(2024, 3, 1);
	Date& decrementReference = --prefixDecrement;
	runner.Check(&decrementReference == &prefixDecrement, "前置 -- 返回原对象引用");
	CheckDate(runner, prefixDecrement, Date(2024, 2, 29),
		"前置 -- 回到闰日");

	Date postfixDecrement(2024, 1, 1);
	const Date decrementOldValue = postfixDecrement--;
	CheckDate(runner, decrementOldValue, Date(2024, 1, 1),
		"后置 -- 返回旧日期");
	CheckDate(runner, postfixDecrement, Date(2023, 12, 31),
		"后置 -- 修改为前一天");
}

void TestFullIntegerOffsets(TestRunner& runner)
{
	const int intMaximum = (std::numeric_limits<int>::max)();
	const int intMinimum = (std::numeric_limits<int>::min)();

	/*
	 * 选择 6000000/1/1 作为锚点，是因为向前或向后移动约 21 亿天后，
	 * 结果仍位于合法年份范围。这样四种表达式都能真正执行成功，
	 * 而不是让 INT_MIN 只走异常分支。
	 *
	 * 尤其是 -INT_MIN 无法用 int 表示；如果实现先写 -day 再转换为
	 * 64 位整数，这些用例会暴露有符号溢出。正确实现必须先提升到 int64_t。
	 */
	const Date anchor(6000000, 1, 1);
	const Date plusMaximum = anchor + intMaximum;
	const Date plusMinimum = anchor + intMinimum;
	const Date minusMaximum = anchor - intMaximum;
	const Date minusMinimum = anchor - intMinimum;

	CheckDate(runner, plusMaximum, Date(11879610, 7, 11),
		"锚点加 INT_MAX");
	CheckDate(runner, plusMinimum, Date(120389, 6, 22),
		"锚点加 INT_MIN");
	CheckDate(runner, minusMaximum, Date(120389, 6, 23),
		"锚点减 INT_MAX");
	CheckDate(runner, minusMinimum, Date(11879610, 7, 12),
		"锚点减 INT_MIN");
	CheckDate(runner, anchor, Date(6000000, 1, 1),
		"极端非修改运算不会改变锚点");

	// 反向运算必须精确回到锚点，不能因中间转换或取绝对值丢失一天。
	CheckDate(runner, plusMaximum - intMaximum, anchor,
		"加 INT_MAX 后可反向恢复");
	CheckDate(runner, plusMinimum - intMinimum, anchor,
		"加 INT_MIN 后可反向恢复");
	CheckDate(runner, minusMaximum + intMaximum, anchor,
		"减 INT_MAX 后可反向恢复");
	CheckDate(runner, minusMinimum + intMinimum, anchor,
		"减 INT_MIN 后可反向恢复");

	// 再对四种极端偏移验证复合赋值及其引用返回语义。
	Date plusAssignMaximum = anchor;
	Date& plusMaxReference = (plusAssignMaximum += intMaximum);
	runner.Check(&plusMaxReference == &plusAssignMaximum,
		"operator+= INT_MAX 返回原对象引用");
	CheckDate(runner, plusAssignMaximum, plusMaximum,
		"operator+= 支持 INT_MAX");

	Date plusAssignMinimum = anchor;
	Date& plusMinReference = (plusAssignMinimum += intMinimum);
	runner.Check(&plusMinReference == &plusAssignMinimum,
		"operator+= INT_MIN 返回原对象引用");
	CheckDate(runner, plusAssignMinimum, plusMinimum,
		"operator+= 支持 INT_MIN");

	Date minusAssignMaximum = anchor;
	Date& minusMaxReference = (minusAssignMaximum -= intMaximum);
	runner.Check(&minusMaxReference == &minusAssignMaximum,
		"operator-= INT_MAX 返回原对象引用");
	CheckDate(runner, minusAssignMaximum, minusMaximum,
		"operator-= 支持 INT_MAX");

	Date minusAssignMinimum = anchor;
	Date& minusMinReference = (minusAssignMinimum -= intMinimum);
	runner.Check(&minusMinReference == &minusAssignMinimum,
		"operator-= INT_MIN 返回原对象引用");
	CheckDate(runner, minusAssignMinimum, minusMinimum,
		"operator-= 支持 INT_MIN");

	// 从最小日期出发的两个精确向量也固定了“日期序号 0”的定义。
	CheckDate(runner, Date(1, 1, 1) + intMaximum,
		Date(5879611, 7, 12), "最小日期加 INT_MAX");
	CheckDate(runner, Date(1, 1, 1) - intMinimum,
		Date(5879611, 7, 13), "最小日期减 INT_MIN");
}

void TestDateDifference(TestRunner& runner)
{
	// 基本方向约定：左日期较晚返回正数，较早返回负数，同日返回零。
	CheckInteger(runner, Date(2024, 6, 15) - Date(2024, 6, 15), 0,
		"相同日期的差为零");
	CheckInteger(runner, Date(2024, 6, 16) - Date(2024, 6, 15), 1,
		"较晚日期减较早日期为正");
	CheckInteger(runner, Date(2024, 6, 15) - Date(2024, 6, 16), -1,
		"较早日期减较晚日期为负");

	// 闰日和完整 400 年周期用于验证公历序号公式。
	CheckInteger(runner, Date(2024, 3, 1) - Date(2024, 2, 28), 2,
		"闰年二月底跨越两天");
	CheckInteger(runner, Date(1900, 3, 1) - Date(1900, 2, 28), 1,
		"世纪普通年二月底只跨越一天");
	CheckInteger(runner, Date(2400, 1, 1) - Date(2000, 1, 1), 146097,
		"完整 400 年公历周期为 146097 天");
	CheckInteger(runner, Date(2000, 7, 1) - Date(2300, 7, 2), -109573,
		"保留原 Test.cpp 的长区间日期差场景");

	/*
	 * 5879611/7/12 的序号恰好是 INT_MAX；
	 * 下一天的序号是 INT_MAX + 1，因此反向差值恰好等于 INT_MIN。
	 * 再多一天就会越过 int 的负边界。
	 */
	const Date epoch(1, 1, 1);
	const Date intMaximumDate(5879611, 7, 12);
	const Date intMaximumPlusOneDate(5879611, 7, 13);
	const Date intMaximumPlusTwoDate(5879611, 7, 14);

	CheckInteger(runner, intMaximumDate - epoch, INT_MAX,
		"日期差可以返回精确的 INT_MAX");
	CheckInteger(runner, epoch - intMaximumPlusOneDate, INT_MIN,
		"日期差可以返回精确的 INT_MIN");
	runner.ExpectThrows<std::overflow_error>(
		[&] { (void)(intMaximumPlusOneDate - epoch); },
		"正日期差超过 INT_MAX 时抛 overflow_error");
	runner.ExpectThrows<std::overflow_error>(
		[&] { (void)(epoch - intMaximumPlusTwoDate); },
		"负日期差小于 INT_MIN 时抛 overflow_error");

	/*
	 * 最大日期与最小日期的跨度极大。该用例既验证溢出检查，
	 * 也会自然淘汰逐日循环几十亿次的低效实现。
	 */
	const Date maximumDate(INT_MAX, 12, 31);
	runner.ExpectThrows<std::overflow_error>(
		[&] { (void)(maximumDate - epoch); },
		"最大日期到最小日期的正差溢出");
	runner.ExpectThrows<std::overflow_error>(
		[&] { (void)(epoch - maximumDate); },
		"最小日期到最大日期的负差溢出");
	CheckDate(runner, epoch, Date(1, 1, 1),
		"日期差计算不会修改左操作数");
	CheckDate(runner, maximumDate, Date(INT_MAX, 12, 31),
		"日期差计算不会修改右操作数");
}

void TestRangeAndStrongGuarantee(TestRunner& runner)
{
	const int intMinimum = (std::numeric_limits<int>::min)();
	const Date minimumDate(1, 1, 1);
	const Date maximumDate(INT_MAX, 12, 31);

	// 紧邻边界的合法运算先通过，避免实现把合法边界也错误地拒绝。
	CheckDate(runner, Date(1, 1, 2) - 1, minimumDate,
		"最小日期上方一天可以安全递减");
	CheckDate(runner, Date(INT_MAX, 12, 30) + 1, maximumDate,
		"最大日期下方一天可以安全递增");

	// 非修改型运算越过支持范围时必须稳定抛出 out_of_range。
	runner.ExpectThrows<std::out_of_range>(
		[&] { (void)(minimumDate - 1); },
		"最小日期再减一天越界");
	runner.ExpectThrows<std::out_of_range>(
		[&] { (void)(maximumDate + 1); },
		"最大日期再加一天越界");
	runner.ExpectThrows<std::out_of_range>(
		[&] { (void)(minimumDate + intMinimum); },
		"最小日期加 INT_MIN 越界");
	runner.ExpectThrows<std::out_of_range>(
		[&] { (void)(maximumDate - intMinimum); },
		"最大日期减 INT_MIN 越界");

	/*
	 * 修改型运算采用强异常保证：必须先完成计算和校验，再写回对象。
	 * 每次捕获异常后再次比较原值，可以发现“改到一半才抛异常”的实现。
	 */
	Date minimumMinusAssign = minimumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { minimumMinusAssign -= 1; },
		"operator-= 在最小日期越界");
	CheckDate(runner, minimumMinusAssign, minimumDate,
		"operator-= 抛异常后对象不变");

	Date maximumPlusAssign = maximumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { maximumPlusAssign += 1; },
		"operator+= 在最大日期越界");
	CheckDate(runner, maximumPlusAssign, maximumDate,
		"operator+= 抛异常后对象不变");

	Date minimumPlusIntMin = minimumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { minimumPlusIntMin += intMinimum; },
		"operator+= INT_MIN 越过最小日期");
	CheckDate(runner, minimumPlusIntMin, minimumDate,
		"operator+= INT_MIN 抛异常后对象不变");

	Date maximumMinusIntMin = maximumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { maximumMinusIntMin -= intMinimum; },
		"operator-= INT_MIN 越过最大日期");
	CheckDate(runner, maximumMinusIntMin, maximumDate,
		"operator-= INT_MIN 抛异常后对象不变");

	// 前置和后置自增、自减也必须继承相同的异常类型与强异常保证。
	Date maximumPrefix = maximumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { ++maximumPrefix; }, "最大日期前置 ++ 越界");
	CheckDate(runner, maximumPrefix, maximumDate,
		"前置 ++ 抛异常后对象不变");

	Date maximumPostfix = maximumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { maximumPostfix++; }, "最大日期后置 ++ 越界");
	CheckDate(runner, maximumPostfix, maximumDate,
		"后置 ++ 抛异常后对象不变");

	Date minimumPrefix = minimumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { --minimumPrefix; }, "最小日期前置 -- 越界");
	CheckDate(runner, minimumPrefix, minimumDate,
		"前置 -- 抛异常后对象不变");

	Date minimumPostfix = minimumDate;
	runner.ExpectThrows<std::out_of_range>(
		[&] { minimumPostfix--; }, "最小日期后置 -- 越界");
	CheckDate(runner, minimumPostfix, minimumDate,
		"后置 -- 抛异常后对象不变");
}

int main()
{
	TestRunner runner;

	RunGroup(runner, "构造与合法性检查", TestConstructionAndValidation);
	RunGroup(runner, "输出接口", TestOutput);
	RunGroup(runner, "比较运算", TestComparisons);
	RunGroup(runner, "普通日期加减", TestOrdinaryArithmetic);
	RunGroup(runner, "前后置自增与自减", TestIncrementAndDecrement);
	RunGroup(runner, "完整 int 偏移范围", TestFullIntegerOffsets);
	RunGroup(runner, "日期差", TestDateDifference);
	RunGroup(runner, "越界与强异常保证", TestRangeAndStrongGuarantee);

	runner.PrintSummary();

	// 约定：全部通过返回 0；只要有一个失败就返回 1，便于脚本和 IDE 判断结果。
	return runner.FailedCount() == 0 ? 0 : 1;
}
