#------------ Add path to system variable -------------------------------------

$path2add = ';C:\Kotlin\kotlinc\bin'
$systemPath = [Environment]::GetEnvironmentVariable('Path');

If (!$systemPath.contains($path2add)) {
    $systemPath += $path2add
    $systemPath = $systemPath 
    [Environment]::SetEnvironmentVariable('Path', $systemPath);
    write-host $systemPath
}

#------------ Delete path from system variable --------------------------------

# $path2delete = ''
# $systemPath = [Environment]::GetEnvironmentVariable('Path');

# $systemPath = $systemPath.replace($path2delete, '')
# $systemPath = $systemPath

# [Environment]::SetEnvironmentVariable('Path', $systemPath);

# write-host "Deleted from path!"
# write-host $systemPath

# #------------ Clean system variable -------------------------------------------

# $systemPath = [Environment]::GetEnvironmentVariable('Path');

# while ($systemPath.contains(';;')) {
#     $systemPath = $systemPath.replace(';;', ';')
# }

# [Environment]::SetEnvironmentVariable('Path', $systemPath);

# write-host "Cleaned path!"
# write-host $systemPath