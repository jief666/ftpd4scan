# ftp4scan
A stripped down version of gnu ftpd. It accepts any password and act as a dropbox. Good for ftp scanning.

Because there is no ftp anymore in High Sierra, I needed a ftp for my network scanner. There is no way I'm entering my main password in that printer (who knows can happen if it get serviced). So I want a ftp that accept any password and refuse to change directory or to modify an remote file.

## Usage
You need to connect with an existing account. Any password is accepted. The current remote directory after login is `[User home directory]/Pictures`.<br/>
Commands to download, change remote directory, delete remote files, etc. are removed.<br/>
File name of uploaded files cannot contains any '/'.

To change the current working directory at login, change the line 87 of `auth.c`. <br/>
It should be a command line argument... I know...

## Getting Started
- Compile with xcode.
- Copy the sample `gftpd.plist` in `/Library/LaunchDaemons`. Adapt the path in `<Program>`.
-  **That's it !**

## Options
There is not config file or external file.<br/>
No pid file, no `ftpusers` file, no `ftpchroot` file (see next paragraph), no log file, no `nologin` file, no welcome file and no login msg file.

NOTE : if you'd like to debug, you can use `[your_path]/ftpd4scan/DerivedData/ftpd4scan/Build/Products/Debug/ftpd4scan` in `gftpd.plist`. That way, you just have to compile with Xcode and retry a connection (If you change dftpd.plist, you have to unload with launchctl and reload).

## Technicality
#### chroot
I'm not using chroot because anyfile created under chrooted env doesn't appear in Finder (In that case, at least). It took me a while to figure out that if you do something else in the directory, the new file eventually appears.<br/>
Because no command is left to download or modify remote file, and because it's on my lan that I share with my wife, I don't feel the need for that extra security.

#### Debug
I modified the server_mode function so it can be debugged under xcode. Program exit at the end of each connection, though.

#### Gnu source
If you're looking for the full Gnu ftpd, ready to compile and debug in Xcode, see : https://github.com/jief666/ftpd_gnu
