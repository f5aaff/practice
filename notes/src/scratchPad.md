# Device Control From CLI

# <u>windows</u>
### <u>eject drive by terminal, by drive letter</u>
- `(New-Object -comObject Shell.Application).Namespace(17).ParseName("*\<Drive Letter\>*:").InvokeVerb("Eject")`
- `(New-Object -comObject Shell.Application).Namespace(17).ParseName("*\<Drive Letter\>*:").InvokeVerb("Eject")`

### <u>info and other commands</u>
<u>get uuid of drive, given the drive letter</u>
- `(Get-WmiObject -Class Win32_Volume | Where-Object { $_.DriveLetter -eq "D:" }).DeviceID`


<u>get drive letter, given uuid of device</u>
- `(Get-CimInstance Win32_Volume | Where-Object {$_.DeviceID -eq "\\?\Volume{$DriveGUID}\"}).DriveLetter`

<u>eject drive by drive letter</u>
- `mountvol <Drive letter> \P`

<u>eject drive by uuid</u><br>
this involves using the command to get the drive letter, as input to the above command.
- `mountvol (Get-CimInstance Win32_Volume | Where-Object {$_.DeviceID -eq "\\?\Volume{$DriveGUID}\"}).DriveLetter \P`

<u>mount drive by uuid</u>
- `mountvol <Drive Letter> : \\?\Volume{$driveGUID}`


### <u>zip and part</u>
no default multi-part zip standard, 3rd party application required.
7z is preferred, either needs to be on path or called from the install location.

- `7z -v\{part size\}\{unit, b k m g (bites, kilobytes, megabytes, gigabytes)\} \{archive name\} \{directory to archive\}`
- `7z -v1g target.zip targetdir/` archive 'targetdir' into 'target.7z' in parts of 1Gb in size.

### <u>reconstruction</u>
reconstructing the archive is simple using 7z, simply pass it the first part, and 7z will look for the rest.
- `7z x {archive part name}`
- `7z x target.zip.001`
the above example will inflate all archive parts, provided they are all present.

# <u>Linux</u>
### <u>eject by terminal</u>
- `eject /dev/sdX` should eject the given drive, can also be given the guid.

### <u>zip and part</u>
-  requires p7zip
- `7z -v\{part size\}\{unit, b k m g (bites, kilobytes, megabytes, gigabytes)\} a \{archive name\} \{directory to archive\}`
- `7z -v1g a target.zip targetdir/`
the only difference to the windows command, is the addition of 'a' before the output and target.

### <u>reconstruction</u>
reconstructing the archive is similar, but using e will flatten the folder structure inside. instead, x is used:
- `7z x {archive part name}`
- `7z x target.zip.001`