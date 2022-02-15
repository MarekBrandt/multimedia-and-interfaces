#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

#include <iostream>

int main()
{
    Mat srcImage;
    Rect rect(10, 10, 100, 200);
    char wielkaLitera = 'A';

    
    //petla wczytuje zdjecia po kolei i rysuje na nich prostakat, zapisuje je jako NAZWA_ORYGINALNA_OUT.jpg

    /*for (int i = 0; i <= 9; i++) {
     
    string path = string("Images/184590_") + wielkaLitera + ".jpg";
    string pathO = string("Images/184590_") + wielkaLitera + "_OUT.jpg";
        
        cout << path << endl;
        srcImage = imread(path);

        if (!srcImage.data) {
            std::cout << "Image couldn't be read\n";
            return 1;
        }

        rectangle(srcImage, rect, Scalar(255, 255, 255), -1);

        imwrite(pathO, srcImage);

        wielkaLitera++;
    }

    srcImage.release();*/

    fstream file;

    file.open("184590.csv", ios::in);

    vector<string> row;
    string line, word, temp;

    wielkaLitera = 'A';

    //petla czyta po wierszu plik csv
    //dla kazdego wiersza poza zerowym, otwiera odpowiednie zdjecie i w konkretnych punktach rysuje kola
    //plik wynikowy zapisany jako NAZWA_ORYGINALNA_OUT2.jpg

    for(int i = 0; i <=9; i++) {

        row.clear();
        getline(file, line);
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == ',') line[j] = '.';
        }
        stringstream s(line);

        if (i == 0) continue;

        
        string path = string("Images/184590_") + wielkaLitera + ".jpg";
        string pathO2 = string("Images/184590_") + wielkaLitera + "_OUT2.jpg";
        srcImage = imread(path);

        if (!srcImage.data) {
            std::cout << "Image couldn't be read\n";
            return 1;
        }

        while (getline(s, word, ';')) {
            row.push_back(word);
        }

        for (int j = 1; j < row.size(); j += 2) {
            circle(srcImage, Point(stoi(row[j]), stoi(row[j+1])), 10, Scalar(255,255,255),-1);
        }

        cout << path << endl;

        imwrite(pathO2, srcImage);

        wielkaLitera++;
    }
    srcImage.release();
    

    /*namedWindow("Marek Brandt");
    moveWindow("Marek Brandt", 0, 0);

    imshow("Marek Brandt", srcImage);
    waitKey();*/
    return 0;
}
