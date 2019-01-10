# Une Piece

A temple run based game made by IMAC

## Build

Here are the bash commands to build the project :

```bash
mkdir build && cd ./build
cmake ../src
make
```

Execute project :
`./UP/<built_file>`

Exemple: `./UP/UP_SDLtemplate`

## References

***Github link***:
<https://github.com/mmmaxou/une-piece>

***Trello link***:
<https://trello.com/b/YK74ga5e/une-piece>

***Assimp tutorial***:
<https://learnopengl.com/Model-Loading/Assimp>
<https://learnopengl.com/Model-Loading/Mesh>
<https://learnopengl.com/Model-Loading/Model>

## Valgrind test the game

```bash
valgrind --leak-check=yes --log-file="valgrind-log.txt" ./UP/UP_main
```

## Profiling test the game

```bash
valgrind --tool=callgrind ./UP/UP_main
kcachegrind callgrind.out.xxxx
```