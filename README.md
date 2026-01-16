Shard is meant to be a personalized tool designed to create shortcuts for your terminal commands

Shard does not mutate your shell, and keeps commands local to the directory you create them in

Shard does not create a config file in your project, but rather in the same folder of the shard executable

Shard has no bloat and is meant to be simple yet effective


Eliminate the need to constantly type out verbose lines, and keep it hidden behind a shortcut. Here is an example:  
shard --config set build as "cmake --build build --config Release"

"cmake --build build --config Release" is now hidden behid this simple command:  
shard build

Now everytime you wake up and open your terminal, you are two words away from building your project. No extra files, no verbose commands, just simplicity.

Commands being local to your directory also means you can have shard commands with the same name in all your projects, each carrying out their own command without naming conflicts.