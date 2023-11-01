BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "WindowsVersions" (
	"Version"	TEXT NOT NULL,
	"Status"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT DEFAULT 'Empty'
);
CREATE TABLE IF NOT EXISTS "macOSVersions" (
	"Version"	TEXT NOT NULL,
	"Status"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT NOT NULL DEFAULT 'Empty'
);
CREATE TABLE IF NOT EXISTS "LinuxVersions" (
	"Version"	TEXT NOT NULL,
	"Status"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL,
	"Url"	TEXT NOT NULL DEFAULT 'Empty'
);
INSERT INTO "WindowsVersions" ("Version","Status","Architecture","Url") VALUES ('0.1','stable\latest','amd64','https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/v0.1_win_amd64/DeepForge_Toolset_0.1_win_amd64.zip'),
 ('0.2','beta','amd64','https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/v0.1_win_amd64/DeepForge_Toolset_0.1_beta_win_amd64.zip'),
 ('0.2','beta\latest','amd64','Empty'),
 ('0.1','stable','amd64','https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/v0.1_win_amd64/DeepForge_Toolset_0.1_win_amd64.zip');
INSERT INTO "macOSVersions" ("Version","Status","Architecture","Url") VALUES ('0.1','beta\latest','amd64','Empty');
INSERT INTO "LinuxVersions" ("Version","Status","Architecture","Url") VALUES ('0.1','beta\latest','amd64','');
COMMIT;
