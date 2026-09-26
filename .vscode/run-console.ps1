param(
    [Parameter(Mandatory = $true)]
    [string]$Program
)

$ErrorActionPreference = 'Stop'
[Console]::OutputEncoding = New-Object System.Text.UTF8Encoding($false)
[Console]::InputEncoding = New-Object System.Text.UTF8Encoding($false)
$OutputEncoding = [Console]::OutputEncoding
$Host.UI.RawUI.WindowTitle = 'C++ 运行结果'
$Host.UI.RawUI.BackgroundColor = 'Black'
$Host.UI.RawUI.ForegroundColor = 'Gray'
Clear-Host

$programExitCode = 1
try {
    if (-not (Test-Path -LiteralPath $Program -PathType Leaf)) {
        throw "找不到程序：$Program"
    }
    & $Program
    $programExitCode = [int]$LASTEXITCODE
}
catch {
    Write-Host $_.Exception.Message -ForegroundColor Red
}

Write-Host ''
Write-Host ('{0} 已退出，代码为 {1} (0x{2}).' -f $Program, $programExitCode, $programExitCode.ToString('X8'))
Write-Host '按任意键关闭此窗口 . . .' -NoNewline
while ([Console]::KeyAvailable) { [void][Console]::ReadKey($true) }
[void][Console]::ReadKey($true)
exit $programExitCode
