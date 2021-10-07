#include "opencv2/highgui/highgui.hpp" // определяет кросс=платформенные функций взаимодействия с оконной системой;
#include "opencv2/imgproc/imgproc.hpp" // определяет основные/традиционные функций цифровой обработки изображений;
// отрисовка кривых и тому подобное
#include <iostream> // iostream - заголовочный файл с классами, функциями и переменными для организации ввода-вывода
#include <stdio.h> //  stdio.h - библиотека, содержащий определения макросов, константы и объявления функций и типов
#include <stdlib.h> // stdlib.h - библиотека, содержит в себе функции, занимающиеся выделением памяти, контролем процесса выполнения программы



using namespace cv;
using namespace std;

Mat img; // создание изображение

int main()
{
	//Запрос от пользователя какой файл ему требуется открыть
	setlocale(LC_ALL, "Russian");
	//string filename; //строчка с названием перменной 
        //cout << "Имя файла "; //вывод значения <<
        //cin >> filename;  // ввод значения >>
        //cout << "Ввели файл "<<filename<<endl; //endl текст будет выведен на след. строке
	//Блок загрузки изображения, Оператор Canny
	char filename[80]; // ash.jpg
	cout << "Введите имя файла, в которой хотите внести изменения, и нажимте Enter" << endl;
	cin.getline(filename, 80);
	cout << "Открыть файл";
	cout << filename << endl;
	//Блок загрузки изображения, Оператор Canny

	Mat img = imread(filename, 1); //создает матрицу. //imread -  считывает изображение из файла, заданного , выводя формат файла из его содержимого.

	namedWindow("source_window", WINDOW_AUTOSIZE); // название окна, авторазмер
	imshow("source_window", img); // отображает изображение в градациях серого на рисунке. использует диапазон отображения по умолчанию для типа данных изображения и оптимизирует свойства рисунка, осей и объекта изображения для отображения изображения
	Mat src_gray, canny_output; //Создание матрицы с названием src_gray и canny_output
	cvtColor(img, src_gray, COLOR_RGB2GRAY); //  cvtColor конвертирует изображения из одного цветового пространства в другое (в монохромное)
	blur(src_gray, src_gray, Size(3, 3)); // размытие
	double otsu_thresh_val = threshold(src_gray, img, 0, 255, THRESH_BINARY | THRESH_OTSU); // нижний и верхний порог, нижний отвечает за шумы изображения, если задать много верхнего, то будет просто черное изображение

	double high_thresh_val = otsu_thresh_val, lower_thresh_val = otsu_thresh_val * 0.5;
	cout << otsu_thresh_val;
	Canny(src_gray, canny_output, lower_thresh_val, high_thresh_val, 3); // оператор обнаружения границ изображения
	
	namedWindow("source_grey_window", WINDOW_AUTOSIZE);
	imshow("source_grey_window", canny_output);
	imwrite("canny_output.jpg", canny_output);
	// Моменты и центр масс findContours
	RNG rng(12345);
	vector<vector<Point>> contours; // генератор случайных чисел
	vector<Vec4i> hierarchy; // Vec4i-это структура для представления вектора с 4 измерениями, каждое значение int. линии-выходной вектор линий

	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0)); // нахождение контуров ,RETR_EXTERNAL - удаляет внутренние контуры  ,CHAIN_APPROX_SIMPLE - нужен для экономии памяти: если линия, то хранит только точки начала и конца
	vector<Moments> mu(contours.size()); // vector<Moments>-это суммарная характеристика пятна, представляющая собой сумму всех точек этого пятна
	//contours.size - кол-во контуров, проходим по всем контурам и определяем центр массы с помощью moments
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}
	//зная 0,1,2 моменты, можно определить координаты центр масс по x and y
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}
	for (int i = 0; i < contours.size(); i++)
	{
		printf("Контур № %d: центр масс - x = %.2f y = %.2f; длина - %.2f\n", i, mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00, arcLength(contours[i],true));
	}
	// Рисование контуров
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3); // CV_8UC3 изображение без знака с 3 каналами
	for (int i = 0; i < contours.size(); i++) 
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)); //Тип Scalar широко используется в OpenCV для передачи значений пикселей, цвет
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point()); //Полученные с помощью функции findContours контуры хорошо бы каким-то образом нарисовать в кадре. Машине это не нужно, зато нам это поможет лучше понять как выглядят найденные алгоритмом контуры. Поможет в этом ещё одна полезная функция — drawContours
		circle(drawing, mc[i], 4, color, -1, 5, 0); // описывает окружность вокруг центра массы
	}
	namedWindow("Контуры", WINDOW_AUTOSIZE);
	imshow("Контуры", drawing);
	
	waitKey(0);
	system("pause");
	return 0;

}
