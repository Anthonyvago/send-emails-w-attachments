Set WshShell = CreateObject("WScript.Shell")
WshShell.Run chr(34) & "<full_system_path_to_.bat_file>" & chr(34), 0
Set WshShell = Nothing