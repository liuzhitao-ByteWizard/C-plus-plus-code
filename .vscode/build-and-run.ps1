param(
    [Parameter(Mandatory = $true)]
    [string]$SourceDirectory,
    [switch]$BuildOnly
)

$ErrorActionPreference = 'Stop'
$sourceFolder = (Resolve-Path -LiteralPath $SourceDirectory).Path
$sourceFiles = @(Get-ChildItem -LiteralPath $sourceFolder -File |
    Where-Object { $_.Extension -in @('.cpp', '.cc', '.cxx', '.c') } |
    Sort-Object Name |
    Select-Object -ExpandProperty FullName)

if ($sourceFiles.Count -eq 0) {
    throw "当前文件夹没有可编译的 C/C++ 源文件：$sourceFolder"
}

$compiler = 'E:\w64devkit\bin\g++.exe'
$buildFolder = Join-Path $sourceFolder 'build\Debug'
[void](New-Item -ItemType Directory -Path $buildFolder -Force)
$program = Join-Path $buildFolder 'outDebug.exe'

Write-Host "正在编译：$sourceFolder"
& $compiler '-g' '-O0' '-Wall' '-Wextra' @sourceFiles '-o' $program
$buildExitCode = $LASTEXITCODE
if ($buildExitCode -ne 0) {
    Write-Host "编译失败，退出码：$buildExitCode" -ForegroundColor Red
    exit $buildExitCode
}
Write-Host '编译成功。'
if ($BuildOnly) { exit 0 }

$consoleScript = Join-Path $PSScriptRoot 'run-console.ps1'
$shellPath = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
$consoleArguments = '-NoLogo -NoProfile -ExecutionPolicy Bypass -File "{0}" -Program "{1}"' -f $consoleScript, $program

# The requested result window owns the program's input/output and stays open.
Start-Process -FilePath $shellPath -ArgumentList $consoleArguments `
    -WorkingDirectory $sourceFolder -WindowStyle Normal

