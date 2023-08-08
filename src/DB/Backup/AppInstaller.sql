BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Applications" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"macOS"	TEXT,
	"Linux"	TEXT
);
CREATE TABLE IF NOT EXISTS "CDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "PythonDevelopmentTools" (
	"Name"	INTEGER NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "DevelopmentPacks" (
	"Number"	TEXT NOT NULL,
	"Language"	TEXT NOT NULL
);
CREATE TABLE IF NOT EXISTS "RustDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "JavaScriptDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "CppDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "GoDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "RubyDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "CSDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "PHPDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "KotlinDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
CREATE TABLE IF NOT EXISTS "JavaDevelopmentTools" (
	"Name"	TEXT NOT NULL,
	"Windows"	TEXT,
	"Linux"	TEXT,
	"macOS"	TEXT
);
INSERT INTO "Applications" ("Name","Windows","macOS","Linux") VALUES ('VSCode','winget install -e --id Microsoft.VisualStudioCode','brew install --cask visual-studio-code','sudo snap install code --classic'),
 ('Docker','winget install -e --id Docker.DockerDesktop','brew install --cask docker','sudo snap install docker'),
 ('Git','winget install --id Git.Git -e --source winget','brew install --cask git','CUSTOM'),
 ('JetBrains WebStorm','winget install -e --id JetBrains.WebStorm','brew install --cask webstorm','sudo snap install webstorm --classic'),
 ('Docker','winget install -e --id Postman.Postman','brew install --cask postman','sudo snap install postman'),
 ('JetBrains RubyMine','winget install -e --id JetBrains.RubyMine','brew install --cask rubymine','sudo snap install postman'),
 ('JetBrains CLion','winget install -e --id JetBrains.CLion','brew install --cask clion','sudo snap install clion --classic'),
 ('JetBrains DataGrip','winget install -e --id JetBrains.DataGrip','brew install --cask datagrip','sudo snap install datagrip --classic'),
 ('JetBrains DataSpell','winget install -e --id JetBrains.DataSpell','brew install --cask dataspell','sudo snap install dataspell --classic'),
 ('Eclipse IDE','CUSTOM','brew install --cask eclipse-ide','sudo snap install eclipse --classic');
INSERT INTO "CDevelopmentTools" ("Name","Windows","Linux","macOS") VALUES ('VSCode','winget install -e --id Microsoft.VisualStudioCode','sudo snap install code --classic','brew install --cask visual-studio-code'),
 ('Docker','winget install -e --id Docker.DockerDesktop','sudo snap install docker','brew install --cask docker');
INSERT INTO "PythonDevelopmentTools" ("Name","Windows","Linux","macOS") VALUES ('VSCode','winget install -e --id Microsoft.VisualStudioCode','sudo snap install code --classic','brew install --cask visual-studio-code'),
 ('Docker','winget install -e --id Docker.DockerDesktop','sudo snap install docker','brew install --cask docker');
INSERT INTO "DevelopmentPacks" ("Number","Language") VALUES ('1','PythonDevelopmentTools');
COMMIT;
