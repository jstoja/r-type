#!/bin/bash

mkdir -p build
cd build
echo "Executing Cmake"
cmake ..
cd ..
echo "Generating Makefile and clean.sh"
echo -e "all:\n\tmake -C build" > Makefile
echo -e "#!/bin/bash\n\nrm -Rf build\nrm -f Makefile clean.sh" > clean.sh
chmod +x clean.sh
echo "Done"
