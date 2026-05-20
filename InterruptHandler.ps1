# 定义文件路径
$filePath = "Core/Src/stm32f1xx_it.c"

# 读取文件内容为数组
$fileContent = Get-Content $filePath

# 定义要删除的函数起始和结束标记
$functionsToRemove = @(
    @{ StartMarker = "void SVC_Handler(void)"; EndMarker = "}" },
    @{ StartMarker = "void PendSV_Handler(void)"; EndMarker = "}" }
)

# 标记变量
$insideTargetBlock = $false
$modifiedContent = @()
$startMarkerFound = $false

# 遍历文件内容，逐行检查
foreach ($line in $fileContent) {
    # 检查是否是函数的起始标记
    foreach ($function in $functionsToRemove) {
        if ($line -like "*$($function.StartMarker)*") {
            $insideTargetBlock = $true
            $startMarkerFound = $true
            break
        }
    }

    # 如果未进入目标块，保留该行
    if (-not $insideTargetBlock) {
        $modifiedContent += $line
    }

    # 如果在目标块中，检查是否到达结束标记
    if ($insideTargetBlock -and $line -like "*$($function.EndMarker)*") {
        $insideTargetBlock = $false
    }
}

# 仅当至少一个起始标记被找到时，写回文件
if ($startMarkerFound) {
    $modifiedContent | Set-Content $filePath
    Write-Host "目标函数已删除，并写回文件：$filePath"
} else {
    Write-Host "未找到任何目标函数，文件未修改。"
}
