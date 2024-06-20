#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>

namespace AlgSortVisUI {
    using namespace std;
    using namespace std::chrono;
    using namespace std::this_thread;
    using namespace System;
    using namespace System::Windows::Forms;

    vector<int> arr;
    float sortingTime;
    int arrSize;
    int timeout = 0;
    bool parsedSize = false;
    bool parsedTimeout = false;

    const int WIDTH = 800;
    const int HEIGHT = 600;
    int NUM_BARS;
    int BAR_WIDTH;
    const int DELAY = 0;

    void timedClose(int time, sf::RenderWindow& window) {
        sleep_for(seconds(time));
        window.close();
    }

    void visualizeSort(sf::RenderWindow& window, const vector<int>& arr) {
        window.clear();

        for (int i = 0; i < NUM_BARS; i++) {
            sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, arr[i]));
            bar.setPosition(i * BAR_WIDTH, HEIGHT - arr[i]);
            bar.setFillColor(sf::Color::White);
            window.draw(bar);
        }

        window.display();
        this_thread::sleep_for(chrono::milliseconds(DELAY));
    }

    void fillArray(vector<int>& arrayNums, int size) {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < size; i++) {
            arrayNums[i] = rand() % 600;
        }
    }

    void bubbleSort(vector<int>& arr, sf::RenderWindow& window) {
        auto start = high_resolution_clock::now();
        int n = arrSize;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    visualizeSort(window, arr);
                }
            }
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        sortingTime = duration.count();
    }

    void insertionSort(vector<int>& arr, sf::RenderWindow& window) {
        auto start = high_resolution_clock::now();
        int n = arrSize;
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                visualizeSort(window, arr);
            }
            arr[j + 1] = key;
            visualizeSort(window, arr);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        sortingTime = duration.count();

    }

    int partition(vector<int>& arr, int low, int high, sf::RenderWindow& window) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
                visualizeSort(window, arr);
            }
        }
        swap(arr[i + 1], arr[high]);
        visualizeSort(window, arr);
        return (i + 1);
    }

    void quickSort(vector<int>& arr, int low, int high, sf::RenderWindow& window) {
        if (low < high) {
            int pi = partition(arr, low, high, window);
            quickSort(arr, low, pi - 1, window);
            quickSort(arr, pi + 1, high, window);
        }
    }

    void selectionSort(vector<int>& arr, sf::RenderWindow& window) {
        auto start = high_resolution_clock::now();
        int n = arrSize;
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            swap(arr[i], arr[min_idx]);
            visualizeSort(window, arr);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        sortingTime = duration.count();
    }

    public ref class MyForm : public System::Windows::Forms::Form {
    public:
        MyForm(void) {
            InitializeComponent();
        }

    protected:
        ~MyForm() {
            if (components) {
                delete components;
            }
        }

    private: System::Windows::Forms::RadioButton^ quickSort_selector;
    private: System::Windows::Forms::RadioButton^ insertionSort_selector;
    private: System::Windows::Forms::RadioButton^ bubbleSort_selector;
    private: System::Windows::Forms::RadioButton^ selectionSort_selector;
    private: System::Windows::Forms::Button^ createArr;
    private: System::Windows::Forms::TextBox^ arraySize_input;
    private: System::Windows::Forms::Label^ arrSize_label;
    private: System::Windows::Forms::Label^ arraySizeLabel;
    private: System::Windows::Forms::Button^ sortBtn;
    private: System::Windows::Forms::Label^ timeoutLabel;
    private: System::Windows::Forms::Label^ timeoutLabel_2;


    private: System::Windows::Forms::TextBox^ timeoutInput;
    private: System::Windows::Forms::Button^ timeoutBtn;
    private: System::Windows::Forms::Label^ sortingTimeLabel;






    protected:
        System::ComponentModel::Container^ components;
#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->quickSort_selector = (gcnew System::Windows::Forms::RadioButton());
            this->insertionSort_selector = (gcnew System::Windows::Forms::RadioButton());
            this->bubbleSort_selector = (gcnew System::Windows::Forms::RadioButton());
            this->selectionSort_selector = (gcnew System::Windows::Forms::RadioButton());
            this->createArr = (gcnew System::Windows::Forms::Button());
            this->arraySize_input = (gcnew System::Windows::Forms::TextBox());
            this->arrSize_label = (gcnew System::Windows::Forms::Label());
            this->arraySizeLabel = (gcnew System::Windows::Forms::Label());
            this->sortBtn = (gcnew System::Windows::Forms::Button());
            this->timeoutLabel = (gcnew System::Windows::Forms::Label());
            this->timeoutLabel_2 = (gcnew System::Windows::Forms::Label());
            this->timeoutInput = (gcnew System::Windows::Forms::TextBox());
            this->timeoutBtn = (gcnew System::Windows::Forms::Button());
            this->sortingTimeLabel = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // quickSort_selector
            // 
            this->quickSort_selector->AutoSize = true;
            this->quickSort_selector->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->quickSort_selector->Location = System::Drawing::Point(208, 445);
            this->quickSort_selector->Name = L"quickSort_selector";
            this->quickSort_selector->Size = System::Drawing::Size(129, 21);
            this->quickSort_selector->TabIndex = 1;
            this->quickSort_selector->TabStop = true;
            this->quickSort_selector->Text = L"Quick Sort";
            this->quickSort_selector->UseVisualStyleBackColor = true;
            // 
            // insertionSort_selector
            // 
            this->insertionSort_selector->AutoSize = true;
            this->insertionSort_selector->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->insertionSort_selector->Location = System::Drawing::Point(208, 406);
            this->insertionSort_selector->Name = L"insertionSort_selector";
            this->insertionSort_selector->Size = System::Drawing::Size(169, 21);
            this->insertionSort_selector->TabIndex = 2;
            this->insertionSort_selector->TabStop = true;
            this->insertionSort_selector->Text = L"Insertion Sort";
            this->insertionSort_selector->UseVisualStyleBackColor = true;
            // 
            // bubbleSort_selector
            // 
            this->bubbleSort_selector->AutoSize = true;
            this->bubbleSort_selector->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->bubbleSort_selector->Location = System::Drawing::Point(208, 361);
            this->bubbleSort_selector->Name = L"bubbleSort_selector";
            this->bubbleSort_selector->Size = System::Drawing::Size(139, 21);
            this->bubbleSort_selector->TabIndex = 3;
            this->bubbleSort_selector->TabStop = true;
            this->bubbleSort_selector->Text = L"Bubble Sort";
            this->bubbleSort_selector->UseVisualStyleBackColor = true;
            // 
            // selectionSort_selector
            // 
            this->selectionSort_selector->AutoSize = true;
            this->selectionSort_selector->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->selectionSort_selector->Location = System::Drawing::Point(208, 484);
            this->selectionSort_selector->Name = L"selectionSort_selector";
            this->selectionSort_selector->Size = System::Drawing::Size(169, 21);
            this->selectionSort_selector->TabIndex = 4;
            this->selectionSort_selector->TabStop = true;
            this->selectionSort_selector->Text = L"Selection Sort";
            this->selectionSort_selector->UseVisualStyleBackColor = true;
            // 
            // createArr
            // 
            this->createArr->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->createArr->Location = System::Drawing::Point(40, 188);
            this->createArr->Name = L"createArr";
            this->createArr->Size = System::Drawing::Size(150, 60);
            this->createArr->TabIndex = 5;
            this->createArr->Text = L"Randomize Array";
            this->createArr->UseVisualStyleBackColor = true;
            this->createArr->Click += gcnew System::EventHandler(this, &MyForm::createArr_Click);
            // 
            // arraySize_input
            // 
            this->arraySize_input->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->arraySize_input->Location = System::Drawing::Point(40, 131);
            this->arraySize_input->Name = L"arraySize_input";
            this->arraySize_input->Size = System::Drawing::Size(150, 24);
            this->arraySize_input->TabIndex = 6;
            this->arraySize_input->TextChanged += gcnew System::EventHandler(this, &MyForm::arraySize_input_TextChanged);
            // 
            // arrSize_label
            // 
            this->arrSize_label->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->arrSize_label->Location = System::Drawing::Point(35, 90);
            this->arrSize_label->Name = L"arrSize_label";
            this->arrSize_label->Size = System::Drawing::Size(198, 26);
            this->arrSize_label->TabIndex = 7;
            this->arrSize_label->Text = L"Enter array size:";
            // 
            // arraySizeLabel
            // 
            this->arraySizeLabel->AutoSize = true;
            this->arraySizeLabel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->arraySizeLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->arraySizeLabel->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->arraySizeLabel->Location = System::Drawing::Point(37, 52);
            this->arraySizeLabel->Name = L"arraySizeLabel";
            this->arraySizeLabel->Size = System::Drawing::Size(148, 17);
            this->arraySizeLabel->TabIndex = 9;
            this->arraySizeLabel->Text = L"Array Size: 0 ";
            // 
            // sortBtn
            // 
            this->sortBtn->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->sortBtn->Location = System::Drawing::Point(208, 545);
            this->sortBtn->Name = L"sortBtn";
            this->sortBtn->Size = System::Drawing::Size(150, 50);
            this->sortBtn->TabIndex = 10;
            this->sortBtn->Text = L"Sort";
            this->sortBtn->UseVisualStyleBackColor = true;
            this->sortBtn->Click += gcnew System::EventHandler(this, &MyForm::sortBtn_Click);
            // 
            // timeoutLabel
            // 
            this->timeoutLabel->AutoSize = true;
            this->timeoutLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->timeoutLabel->Location = System::Drawing::Point(337, 52);
            this->timeoutLabel->Name = L"timeoutLabel";
            this->timeoutLabel->Size = System::Drawing::Size(188, 17);
            this->timeoutLabel->TabIndex = 11;
            this->timeoutLabel->Text = L"Timeout: 0 seconds";
            // 
            // timeoutLabel_2
            // 
            this->timeoutLabel_2->AutoSize = true;
            this->timeoutLabel_2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->timeoutLabel_2->Location = System::Drawing::Point(337, 90);
            this->timeoutLabel_2->Name = L"timeoutLabel_2";
            this->timeoutLabel_2->Size = System::Drawing::Size(198, 17);
            this->timeoutLabel_2->TabIndex = 14;
            this->timeoutLabel_2->Text = L"Enter timeout time:";
            // 
            // timeoutInput
            // 
            this->timeoutInput->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->timeoutInput->Location = System::Drawing::Point(350, 131);
            this->timeoutInput->Name = L"timeoutInput";
            this->timeoutInput->Size = System::Drawing::Size(150, 24);
            this->timeoutInput->TabIndex = 13;
            this->timeoutInput->TextChanged += gcnew System::EventHandler(this, &MyForm::timeoutInput_TextChanged);
            // 
            // timeoutBtn
            // 
            this->timeoutBtn->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->timeoutBtn->Location = System::Drawing::Point(350, 188);
            this->timeoutBtn->Name = L"timeoutBtn";
            this->timeoutBtn->Size = System::Drawing::Size(150, 60);
            this->timeoutBtn->TabIndex = 12;
            this->timeoutBtn->Text = L"Set Timeout";
            this->timeoutBtn->UseVisualStyleBackColor = true;
            this->timeoutBtn->Click += gcnew System::EventHandler(this, &MyForm::timeoutBtn_Click);
            // 
            // sortingTimeLabel
            // 
            this->sortingTimeLabel->AutoSize = true;
            this->sortingTimeLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
            this->sortingTimeLabel->Location = System::Drawing::Point(109, 309);
            this->sortingTimeLabel->Name = L"sortingTimeLabel";
            this->sortingTimeLabel->Size = System::Drawing::Size(328, 17);
            this->sortingTimeLabel->TabIndex = 16;
            this->sortingTimeLabel->Text = L"Time taken by sorting: 0 seconds";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::LightSteelBlue;
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
            this->ClientSize = System::Drawing::Size(602, 613);
            this->Controls->Add(this->sortingTimeLabel);
            this->Controls->Add(this->timeoutLabel_2);
            this->Controls->Add(this->timeoutInput);
            this->Controls->Add(this->timeoutBtn);
            this->Controls->Add(this->timeoutLabel);
            this->Controls->Add(this->sortBtn);
            this->Controls->Add(this->arraySizeLabel);
            this->Controls->Add(this->arrSize_label);
            this->Controls->Add(this->arraySize_input);
            this->Controls->Add(this->createArr);
            this->Controls->Add(this->selectionSort_selector);
            this->Controls->Add(this->bubbleSort_selector);
            this->Controls->Add(this->insertionSort_selector);
            this->Controls->Add(this->quickSort_selector);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Sorting Algorithms Visualizer";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        System::Void arraySize_input_TextChanged(System::Object^ sender, System::EventArgs^ e) {
            if (Int32::TryParse(arraySize_input->Text, arrSize)) {
                parsedSize = true;
                NUM_BARS = arrSize;
                BAR_WIDTH = WIDTH / NUM_BARS;
            }
            else {
                parsedSize = false;
            }
        }

    private:
        System::Void createArr_Click(System::Object^ sender, System::EventArgs^ e) {
            if (parsedSize) {
                if (arrSize < 2 || arrSize > 800) {
                    this->arraySizeLabel->Text = "Error: Array size 2-800";
                }
                else {
                    this->arraySizeLabel->Text = "Array Size: " + arrSize.ToString();
                    arr.resize(arrSize);
                    fillArray(arr, arrSize);
                }
            }
            else {
                this->arraySizeLabel->Text = "Error: Enter an integer.";
            }
        }

    private:
        System::Void sortBtn_Click(System::Object^ sender, System::EventArgs^ e) {
            sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualisator");

            if (arrSize == NULL) {
                this->arraySizeLabel->Text = "Enter the array size first.";
            }
            else {
                while (window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }

                        if (bubbleSort_selector->Checked) {
                            bubbleSort(arr, window);
                            timedClose(timeout, window);
                        }
                        else if (insertionSort_selector->Checked) {
                            insertionSort(arr, window);
                            timedClose(timeout, window);
                        }
                        else if (quickSort_selector->Checked) {
                            auto start = high_resolution_clock::now();
                            quickSort(arr, 0, arrSize - 1, window);
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<milliseconds>(stop - start);
                            sortingTime = duration.count();
                            timedClose(timeout, window);
                        }
                        else if (selectionSort_selector->Checked) {
                            selectionSort(arr, window);
                            timedClose(timeout, window);
                        }
                        this->sortingTimeLabel->Text = "Time taken by sorting: " + sortingTime / 1000 + " seconds.";
                    }
                }
            }
        }
    private: System::Void timeoutInput_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        if (Int32::TryParse(timeoutInput->Text, timeout)) {
            parsedTimeout = true;
        }
        else {
            parsedTimeout = false;
        }
    }

    private: System::Void timeoutBtn_Click(System::Object^ sender, System::EventArgs^ e) {
        if (parsedTimeout) {
            if (timeout >= 0) {
                this->timeoutLabel->Text = "Timeout: " + timeout.ToString() + " seconds";
                this->timeoutLabel_2->Text = "Enter timeout time:";
            }
            else {
                this->timeoutLabel_2->Text = "Timeout should be >= 0";
                timeout = 0;
                this->timeoutLabel->Text = "Timeout: " + timeout.ToString() + " seconds";
            }
        }
        else {
            this->timeoutLabel_2->Text = "Enter an integer";
            timeout = 0;
            this->timeoutLabel->Text = "Timeout: " + timeout.ToString() + " seconds";
        }
    }
    };
}