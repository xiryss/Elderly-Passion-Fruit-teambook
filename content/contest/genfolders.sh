for f in {a..z}
do
    mkdir $f
    cp template.cpp $f/$f.cpp
    touch $f/in
done