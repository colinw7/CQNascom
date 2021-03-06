static const char *
nascom_chars[] = {
  /* width height num_colors chars_per_pixel x_hot y_hot */
  "128 256 2 1 0 0",

  /* colors */
  ". s symbol1 c #ffffff m white",
  "# s symbol2 c #000000 m black",

  /* pixels */
  ".#######.#######....#..........#..#......#######...........###.....#.............#######............#..............###.....###..",
  ".#.....#.#..........#..........#...#.....#.....#.......#..#...#...#.........#...............#.......#.......#.....#...#...#...#.",
  ".#.....#.#..........#..........#....#....##...##......#..#.....#.#####.......#..............#.....#.#.#....#.....##...##.#.....#",
  ".#.....#.#..........#..........#.....#...#.#.#.#.....#...#.....#..#...#.......#.............#......###....#......#.#.#.#.#.....#",
  ".#.....#.#..........#..........#..#####..#..#..#.#..#....#.....#...#...#.#######.#######.#..#..#....#....#######.#..#..#.#..#..#",
  ".#.....#.#..........#..........#...#.....#.#.#.#.#.#.....#######.......#......#...........#.#.#..#..#..#..#......#.#.#.#.#.....#",
  ".#.....#.#..........#..........#....#....##...##.##........#.#.........#.....#.............###....#.#.#....#.....##...##.#.....#",
  ".#.....#.#..........#..........#.....#...#.....#.#.........#.#.........#....#...............#......###......#.....#...#...#...#.",
  ".#######.#.......#######.#######......#..#######.........###.###.......#.........#######............#..............###.....###..",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  ".#######...###.....###.....###.....###............#####........#.#######....#.....####.....###...#######.#######.#######.#######",
  ".#.....#..#.#.#...#...#...#...#...#.#.#....#...#..#...#........#.#.....#....#....#....#...#...#..#..#..#.#.....#.#.....#.#..#..#",
  ".#.....#.#..#..#.#.....#.#.....#.#..#..#....#.#...#...#........#..#...#.....#....#....#..#.....#.#..#..#.#.....#.#.....#.#..#..#",
  ".#.....#.#..#..#.#.....#.#.....#.#..#..#.....#....#...#........#...#.#.....###...#.......#.....#.#..#..#.#.....#.#.....#.#..#..#",
  ".#######.#..####.#..####.####..#.####..#.#..#.#...#...#..#######....#......###....##.....#######.####..#.####..#.#..####.#..####",
  ".#.....#.#.....#.#..#..#.#..#..#.#.....#.#.#...#..#...#........#...#.#......#.......#....#.....#.#.....#.#..#..#.#..#..#.#.....#",
  ".#.....#.#.....#.#..#..#.#..#..#.#.....#.##.......#...#........#..#...#.....#.......#....#.....#.#.....#.#..#..#.#..#..#.#.....#",
  ".#.....#..#...#...#.#.#...#.#.#...#...#..#........#...#........#.#.....#....#.............#...#..#.....#.#..#..#.#..#..#.#.....#",
  ".#######...###.....###.....###.....###...........##...##.......#.#######....#.......#......###...#######.#######.#######.#######",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "............#.....#..#.....###......#.....#.......###.......##.......#.....#....................................................",
  "............#.....#..#....#...#...######.#.#...#.#...#......##......#.......#.......#.......#..................................#",
  "............#.....#..#....#......#..#.....#...#..#...#......#......#.........#...#..#..#....#.................................#.",
  "............#.............#......#..#........#....#.#......#.......#.........#....#.#.#.....#................................#..",
  "............#............###......#####.....#......#...............#.........#.....###...#######.........#######............#...",
  "..........................#.........#..#...#......#.#..#...........#.........#....#.#.#.....#..............................#....",
  "..........................#.........#..#..#...#..#...##............#.........#...#..#..#....#.............................#.....",
  "............#.............#....#.######..#...#.#.#...##.............#.......#.......#.......#......##..............##....#......",
  "............#............######.....#.........#...###..#.............#.....#.......................##..............##...........",
  "...................................................................................................#............................",
  "..................................................................................................#.............................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "..#####.....#.....#####...#####.......#..#######...####..#######..#####...#####......................#.............#.......####.",
  ".#.....#...##....#.....#.#.....#.....##..#........#......#.....#.#.....#.#.....#....................#...............#.....#....#",
  ".#....##..#.#..........#.......#....#.#..#.......#............#..#.....#.#.....#...................#.................#....#....#",
  ".#...#.#....#.........#........#...#..#..#####...#...........#...#.....#.#.....#...##......##.....#.......#####.......#........#",
  ".#..#..#....#......###.....####...#...#.......#..######.....#.....#####...######...##......##....#.....................#.....##.",
  ".#.#...#....#.....#............#.#....#........#.#.....#...#.....#.....#.......#..................#.......#####.......#.....#...",
  ".##....#....#....#.............#.#######.......#.#.....#...#.....#.....#.......#...................#.................#......#...",
  ".#.....#....#....#.......#.....#......#..#....#..#.....#...#.....#.....#......#....##......##.......#...............#...........",
  "..#####...#####..#######..#####.......#...####....#####....#......#####...####.....##......##........#.............#........#...",
  "...........................................................................................#....................................",
  "..........................................................................................#.....................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "...####....###...######....####..#####...#######.#######...####..#.....#..#####....#####.#.....#.#.......#.....#.#.....#...###..",
  "..#....#..#...#...#....#..#....#..#...#..#.......#........#....#.#.....#....#........#...#....#..#.......##...##.##....#..#...#.",
  ".#..##.#.#.....#..#....#.#........#....#.#.......#.......#.......#.....#....#........#...#...#...#.......#.#.#.#.#.#...#.#.....#",
  ".#.#.#.#.#.....#..#....#.#........#....#.#.......#.......#.......#.....#....#........#...#..#....#.......#..#..#.#..#..#.#.....#",
  ".#.#.#.#.#######..#####..#........#....#.####....####....#.......#######....#........#...#.#.....#.......#..#..#.#...#.#.#.....#",
  ".#.####..#.....#..#....#.#........#....#.#.......#.......#..####.#.....#....#........#...##.#....#.......#.....#.#....##.#.....#",
  ".#.......#.....#..#....#.#........#....#.#.......#.......#.....#.#.....#....#........#...#...#...#.......#.....#.#.....#.#.....#",
  "..#......#.....#..#....#..#....#..#...#..#.......#........#....#.#.....#....#....#...#...#....#..#.......#.....#.#.....#..#...#.",
  "...####..#.....#.######....####..#####...#######.#.........####..#.....#..#####...###....#.....#.#######.#.....#.#.....#...###..",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  ".######....###...######...#####..#######.#.....#.#.....#.#.....#.#.....#.#.....#.#######..####............####..................",
  ".#.....#..#...#..#.....#.#.....#....#....#.....#.#.....#.#.....#.#.....#.#.....#.......#..#......#...........#......#...........",
  ".#.....#.#.....#.#.....#.#..........#....#.....#.#.....#.#.....#..#...#...#...#.......#...#.......#..........#.....###..........",
  ".#.....#.#.....#.#.....#.#..........#....#.....#..#...#..#.....#...#.#.....#.#.......#....#........#.........#....#.#.#.........",
  ".######..#.....#.######...#####.....#....#.....#..#...#..#..#..#....#.......#.......#.....#.........#........#...#..#..#........",
  ".#.......#..#..#.#..#..........#....#....#.....#...#.#...#..#..#...#.#......#......#......#..........#.......#......#...........",
  ".#.......#...#.#.#...#.........#....#....#.....#...#.#...#.#.#.#..#...#.....#.....#.......#...........#......#......#...........",
  ".#........#...#..#....#..#.....#....#....#.....#....#....##...##.#.....#....#....#........#............#.....#......#...........",
  ".#.........###.#.#.....#..#####.....#.....#####.....#....#.....#.#.....#....#....#######..####............####...........#######",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "...##............#....................#.............##...........#.......................#.........##...........................",
  "...##............#....................#............#..#..........#..........#.........#..#..........#...........................",
  "....#............#....................#............#.............#.......................#..........#...........................",
  ".....#....####...#.###....####....###.#...####.....#......###.#..#.###.....##........##..#...#......#....###.##..#.###....####..",
  "..............#..##...#..#....#..#...##..#....#..#####...#...##..##...#.....#.........#..#..#.......#....#..#..#.##...#..#....#.",
  "..........#####..#....#..#.......#....#..######....#.....#....#..#....#.....#.........#..#.#........#....#..#..#.#....#..#....#.",
  ".........#....#..#....#..#.......#....#..#.........#.....#....#..#....#.....#.........#..##.#.......#....#..#..#.#....#..#....#.",
  ".........#....#..##...#..#....#..#...##..#.........#.....#...##..#....#.....#.........#..#...#......#....#..#..#.#....#..#....#.",
  "..........####.#.#.###....####....###.#...####.....#......###.#..#....#....###........#..#....#....###...#..#..#.#....#...####..",
  "..............................................................#.......................#.........................................",
  ".........................................................#....#...................#...#.........................................",
  "..........................................................####.....................###..........................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "............................................................................................##......#......##....#######..#..#..",
  "...................................#.......................................................#........#........#...........#..#..#",
  "...................................#.......................................................#........#........#.............#..#.",
  ".#.###....###.#..#.###....####...#####...#....#..#.....#.#.....#.#....#..#....#..######....#.................#............#..#..",
  ".##...#..#...##..##...#..#....#....#.....#....#..#.....#.#..#..#..#..#...#....#......#....#...................#..........#..#..#",
  ".#....#..#....#..#........##.......#.....#....#..#.....#.#..#..#...##....#....#.....#......#........#........#.............#..#.",
  ".#....#..#....#..#..........##.....#.....#....#...#...#..#..#..#...##....#....#....#.......#........#........#............#..#..",
  ".##...#..#...##..#.......#....#....#..#..#...##....#.#...#..#..#..#..#...#...##...#........#........#........#...........#..#..#",
  ".#.###....###.#..#........####......##....###.#.....#.....##.##..#....#...###.#..######.....##.............##..............#..#.",
  ".#............#...............................................................#.................................................",
  ".#............#..........................................................#....#.................................................",
  ".#............#...........................................................####..................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  ".#.#.#.#........#..............##################..............#.......##........................###.###........................",
  "#.#.#.#.##..##...#............#..##############.##............##......#..#.......................###.###########.######...######",
  ".#.#.#.###..##...#............#..##############.##............##.....#....#......................###.###########.#####.....#####",
  "#.#.#.#...##..##..#..........#....############..###..........###....#......#.....................###.###########.####..#.#..####",
  ".#.#.#.#..##..##..#..........#....############..###..........###...#........#....................###.###.........###..##.##..###",
  "#.#.#.#.##..##.....#........#......##########...####........####..#..........#...................###.###.........##..###.###..##",
  ".#.#.#.###..##.....#........#......##########...####........####.#............#..................###.###########.#..####.####..#",
  "#.#.#.#...##..##....#......#........########....#####......######..............###............##.###.###########...#####.#####..",
  ".#.#.#.#..##..##....#......#........########....#####......#####..................#..........#...###.###########..######.######.",
  "#.#.#.#..............#....#..........######.....######....######...................#........#...................................",
  ".#.#.#.#.............#....#..........######.....######....######....................#......#....................................",
  "#.#.#.#...............#..#............####......#######..#######.....................#....#.....................................",
  ".#.#.#.#..............#..#............####......#######..#######......................#..#......................................",
  "#.#.#.#................##..............##.......################.......................##.......................................",
  ".#.#.#.#...............##..............##.......################.......................##.......................................",
  "#.#.#.#................##..............##.......################.......................##.......................................",
  "....................#.......#.......#.......#.......#.......#...............#...............#########...########...#.#..........",
  "....................#.......#.......#.......#.......#.......#...............#...............#.......#..............#.#..........",
  "....................#.......#.......#.......#.......#.......#...............#...............#.......#..............#.#..........",
  "....................#.......#.......#.......#.......#.......#...............#...............#.......#............#######.##.##..",
  "....................#.......#.......#.......#.......#.......#...............#...............#.......#..............#.#..#..#..#.",
  "....................#.......#.......#.......#.......#.......#...............#...............#.......#..............#.#..#..#..#.",
  "....................#.......#.......#.......#.......#.......#...............#...............#.......#............#######.##.##..",
  "....#########.......#########.......#.......#################...#############################.......####...........#.#..........",
  "....#.......#.......................#.......#.......#.......#.......................#..............................#.#..........",
  "....#.......#.......................#.......#.......#.......#.......................#..............................#.#..........",
  "....#.......#.......................#.......#.......#.......#.......................#...........................................",
  "....#.......#.......................#.......#.......#.......#.......................#...........................................",
  "....#.......#.......................#.......#.......#.......#.......................#...........................................",
  "....#.......#.......................#.......#.......#.......#.......................#...........................................",
  "....#.......#.......................#.......#.......#.......#.......................#...........................................",
  "....#.......#.......................#.......#.......#.......#.......................#...........................................",
  "..........#.......#......###................................###..........................#######....................#...........",
  ".........##......##.........#..............................#..............................#.........................#.......#...",
  "..........#.......#.......##................###............#........................#......#...........#............#...........",
  "..........#.......#.........#..............#...#............##............######...#.#......#.........#...##.....#######........",
  ".........###.....###.....###......##...#...#...#..............#...#...#..#.#.#.....#.#.......#...#######.#..#..#....#....#######",
  "..............#......##.......#..#..#.#....####..#.....#....###...#...#....#.#....#...#.....#.......#........##.....#...........",
  ".............##.....#..#.....##..#...#.....#...#..#...#....#..#...#...#....#.#....#...#....#........#...............#...........",
  "............#.#.......#.....#.#..#..#.#....#...#...#.#.....#..#...#...#....#.#...#.....#..#......#######..##................#...",
  "...........#####.....#.....#####..##...#...####.....#.......##....####.#...#.#...#######.#######..#......#..#..#................",
  "..............#.....####......#............#.......#.#............#..............................#...........##..#######........",
  "...........................................#.......#.#............#.............................................................",
  "...........................................#........#.............#.............................................................",
  "..................................................................#.............................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "................................................................................................................................",
  "...#........#........###....#....#.....#..####....####....####..................################...#.....#...#.....#......###...",
  ".#..#......#..#......#.....#.#....#...#......#....#.......#..#..................################..###...###.###...###.....###...",
  "..#..#....#..#.......#....#...#....#.#.......#....#.......#..#....#####...#####.##....####....##.#####..#######...###...#######.",
  "...#..#..#..#........#...#.....#....#.....####....####....####...#.....#.########......##.####.########..#####...#####..#######.",
  "....#..##..#.........#...........#######...##......##......##....#.....#.########......##.####.########..#####..#######....#....",
  "...#..#..#..#.....#..#..............#.....####....####..########.#.....#.########......##.####.#.#.#.#....###....#####.....#....",
  "..#..#....#..#...#.#.#............#####..######..######.#.##.#.#.#.....#.########......##.####.#...#......###.....###......#....",
  ".#..#......#..#.....##..............#...#.####.##.####.##.#.##.#.#.....#.#########....####....##...#.......#......###....#####..",
  "...#........#........#..............#...#.####.##.####.##.##.#.#..#####...#####.################.#####.............#............",
  "........................................#.####.##.####.##.#.##.#................################................................",
  "..........................................####....####....####..................................................................",
  "..........................................#.#......#.#....#..#..................................................................",
  ".........................................#...#....#...#...#..#..................................................................",
  ".........................................#....#..#....#...#..#..................................................................",
  ".........................................#....#..#....#...#..#..................................................................",
  "........................................##...##..##...##.##..##.................................................................",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "................................####....####....####....####....................................####....####....####....####....",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "................####....####....................####....####....................####....####....................####....####....",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "........####............####............####............####........############....############....############....############",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####################....####....####################....####....####################....####....####################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
  "....####....####....####....####################################....####....####....####....####################################",
};
