 #!/usr/bin/bash
echo "g++ -Wall -std=c++11 board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp -o arduino"
g++ -Wall -std=c++11 board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp -o arduino
