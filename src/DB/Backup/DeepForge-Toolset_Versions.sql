BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "macOSVersions" (
	"Version"	TEXT NOT NULL,
	"Channel"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT NOT NULL DEFAULT 'Empty'
);
CREATE TABLE IF NOT EXISTS "LinuxVersions" (
	"Version"	TEXT NOT NULL,
	"Channel"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT NOT NULL DEFAULT 'Empty'
);
CREATE TABLE IF NOT EXISTS "WindowsVersions" (
	"Version"	TEXT NOT NULL,
	"Channel"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT DEFAULT 'Empty'
);
CREATE TABLE IF NOT EXISTS "UpdateManager_Linux" (
	"Version"	TEXT NOT NULL,
	"Channel"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT NOT NULL DEFAULT 'Empty'
);
CREATE TABLE IF NOT EXISTS "UpdateManager_Windows" (
	"Version"	TEXT NOT NULL,
	"Channel"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT NOT NULL DEFAULT 'Empty'
);
CREATE TABLE IF NOT EXISTS "UpdateManager_macOS" (
	"Version"	TEXT NOT NULL,
	"Channel"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT NOT NULL DEFAULT 'Empty'
);
INSERT INTO "macOSVersions" ("Version","Channel","Architecture","Url") VALUES ('0.1','beta','amd64','https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/v0.1_macOS_amd64/DeepForge_Toolset_0.1_macOS_amd64.zip');
INSERT INTO "LinuxVersions" ("Version","Channel","Architecture","Url") VALUES ('0.1','stable','amd64','https://github.com/DeepForge-Tech/DeepForge-Toolset/releases/download/v0.1_linux_amd64/DeepForge-Toolset_0.1_linux_amd64.zip');
INSERT INTO "WindowsVersions" ("Version","Channel","Architecture","Url") VALUES ('0.1','stable','amd64','https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/v0.1_win_amd64/DeepForge_Toolset_0.1_win_amd64.zip');
INSERT INTO "UpdateManager_Linux" ("Version","Channel","Architecture","Url") VALUES ('0.1','stable','amd64','https://github.com/DeepForge-Tech/UpdateManager/releases/download/v0.1_linux_amd64/UpdateManager_0.1_linux_amd64.zip');
INSERT INTO "UpdateManager_Windows" ("Version","Channel","Architecture","Url") VALUES ('0.1','stable','amd64','https://github.com/DeepForge-Technology/UpdateManager/releases/download/v0.1_win_amd64/UpdateManager.exe');
COMMIT;
