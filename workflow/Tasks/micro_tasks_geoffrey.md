Template:

**_ Macro Task Name _**

- [ ] Micro Task A 
- [ ] Micro Task B
- [ ] Micro Task C

----------------- TODO -----------------
**_ events  _**
- [x] Refactor / Comment previous branches work
- [x] Creer des placeholders de fonctions d'actions
- [x] Initialiser le tableau de psf on fly avec les bindings dans assign_value
- [x] Remplir la fonction d'action exit
- [x] Linker les fonctions d'actions avec le systeme de detection d'appui
- [x] Developper la liste de faces en une liste d'indices et une liste de materiaux
- [x] Placer l'origine du mesh a son centre
- [ ] Proteger tous les calls OpenGL
- [ ] Empecher la repetition frame par frame des boutons toggles
- [ ] Ajouter un setting fullscreen
- [ ] Refactor + comment review complets

----------------- DONE -----------------

**_ settings _**
- [x] Creer un fichier settings
- [x] Mapper le fichier et le decouper en lignes
- [x] Interpreter les lignes une a une pour remplir la structure settings

**_ obj_parser_basics  _**
- [x] Creer le loading wrapper pour les fichiers obj (readlines)
- [x] Identifier les types de chaque ligne pour l'obj
- [x] Creer les loaders pour chaque identifiant
- [x] Link les identifiants aux loaders pour remplir les data structures
- [x] Securiser le parser
- [x] Refactor / comments
- [x] Identifier les types de lignes pour le mtl
- [x] Creer les loaders (mtllib et usemtl)
- [x] Link les identifiants aux loaders pour remplir les data structures
- [x] Securiser les loaders
- [x] Definir un nom de mesh par defaut et supprimer l'erreur no defined object
- [x] Refactor / comments
- [x] Free toutes les allocations faites par init

**_ key_binder  _**
- [x] Creer un tableau de correspondance char* <=> GLFW_KEY_*
- [x] Importer la lib glad et lui ajouter un Makefile dependant de celui de scop
- [x] Documenter les settings + bindings dans le README
- [x] Ajouter les identifiants d'actions aux proprietes a charger dans Settings.toml
- [x] Creer un tableau de pointeurs sur fonction qui match les keys
