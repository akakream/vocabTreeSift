# vocabSiftTree

Image recognition using SIFT detector and vocabulary tree

## Getting Started

Install OpenCV

SIFT detector is already built-in. If you want to download it seperately here you go:
```
cd ~
wget https://tubcloud.tu-berlin.de/s/HSa2a5wwl81vfY3/download
unzip download
cd ocv_sift_detector/build
cmake ..
make
sudo make install
```

Vocabulary Search Tree is also already built-in except VocabSiftTree\trees\tree.5.10 (it was too big to upload to github) and the code is from the github repository found under https://github.com/snavely/VocabTree2. The repository also contains information about the implemented method. You should download and only include tree.5.10 under VocabSiftTree\trees.
```
cd ~
wget https://github.com/snavely/VocabTree2/archive/master.zip
unzip master.zip

```  
Enter directory and start compilation:
``` 
cd VocabTree2-master/
make
``` 

The repository gave me a couple of errors. They disappear when options not recognized are removed from the corresponding Make-config and Makefile files. The files responsible for the messages can be easily found using the following command:

```
grep -r ’errorstring’ ./
```

## Usage

Step 1
Create a main folder under VocabSiftTree
Create a db and queries folder under the main folder
Put the images for your database under the folder db
Put the images to querry (recognize) under the folder queries

Step2
All the mentioned scripts can be found under the folder scripts!

Copy the ocvsift.sh and paste it under the folders db and queries
Run ocvsift.sh, this will create corresponding keys for each image in the db and queries folders.
Copy the createdblist.sh, createdbdllist.sh, createquerieslist.sh and paste it under your main folder. Then run them. This will create list_db.txt, list_db_ld.txt and list_queries.txt.

Step3
Unfortunately in this step you have to tag your db manually. In the future I will solve this problem, I do not have time right now. In list_db_ld.txt you have to tag the images starting from 0. Same group of images will have the same number. For an example see the example/list_db_ld.txt.

Step4
Run the script.linux.sh
```
sh script.linux.sh
```

Step5
Display the results which where written to the matches.txt file.
```
more matches.txt
```

PS: If you can't run the bash script try:
```
chmod +x <NameoftheScript>
```
Run the script
```
./<NameoftheScript>
```

## How to interpret the matches

The output matches file has three columns:
-the index of the query image to match
-the index of a well-matching image from the database
-the matching score between these images

Example:
0 19 0.0118
0 0 0.0112
0 3 0.0109
1 20 0.0144
1 25 0.0114
1 24 0.0086
2 8 0.0086
2 9 0.0061
2 23 0.0055
3 12 0.0067
3 9 0.0067
3 6 0.0066
4 27 0.0078
4 15 0.0076
4 16 0.0074
5 20 0.0427
5 24 0.0090
5 23 0.0083
6 27 0.0103
6 24 0.0048
6 25 0.0044

## Example

An example can be found under the folder example

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/akakream/vocabSiftTree/tags). 

## Authors

* **Ahmet Kerem Aksoy** - [akakream](https://github.com/akakream)

See also the list of [contributors](https://github.com/akakream/vocabSiftTree/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to snavely for providing the code for vocabulary tree
* Thanks to David Lowe for the SIFT binary

