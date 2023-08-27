BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "WindowsVersions" (
	"Version"	TEXT NOT NULL,
	"Status"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL
);
CREATE TABLE IF NOT EXISTS "macOSVersions" (
	"Version"	TEXT NOT NULL,
	"Status"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL
);
CREATE TABLE IF NOT EXISTS "LinuxVersions" (
	"Version"	TEXT NOT NULL,
	"Status"	TEXT NOT NULL,
	"Architecture"	TEXT NOT NULL
);
INSERT INTO "WindowsVersions" ("Version","Status","Architecture") VALUES ('0.1','beta\latest','amd64');
INSERT INTO "macOSVersions" ("Version","Status","Architecture") VALUES ('0.1','beta\latest','amd64');
INSERT INTO "LinuxVersions" ("Version","Status","Architecture") VALUES ('0.1','beta\latest','amd64');
COMMIT;
