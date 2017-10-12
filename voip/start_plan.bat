TASKKILL /F /IM "eSpace SoftPhone.exe"

ping -n 5 127.0.0.1>nul

d:
cd D:\Program Files (x86)\eSpace_UC\eSpace SoftPhone
start "CS" "eSpace SoftPhone.exe" "/m"