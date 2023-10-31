#include <iostream>
#include <fstream>
#include <vector>

class TemperatureChart {
private:
    std::vector<int> temperatures;

public:
    void readTemperaturesFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file) {
            std::cerr << "Error: Unable to open the file." << std::endl;
            return;
        }

        int temp;
        while (file >> temp) {
            if (temp >= -30 && temp <= 120) {
                temperatures.push_back(temp);
            }
            else {
                std::cerr << "Warning: Ignoring out-of-range temperature: " << temp << std::endl;
            }
        }
        file.close();
    }

    void generateChart() {
        const int chartWidth = 50;
        const int range = 3;
        const int numBars = (120 - (-30)) / range + 1;

        int histogram[numBars] = { 0 };

        for (int temp : temperatures) {
            int index = (temp - (-30)) / range;
            histogram[index]++;
        }

        std::cout << "Temperature Bar Chart (Scale: -30 to 120 degrees)" << std::endl;

        for (int i = 0; i < numBars; i++) {
            int lowerBound = -30 + i * range;
            int upperBound = lowerBound + range - 1;

            std::cout << lowerBound << "-" << upperBound << " | ";
            for (int j = 0; j < histogram[i]; j++) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    TemperatureChart chart;
    chart.readTemperaturesFromFile("temperature_data.txt"); // Replace with your file path
    chart.generateChart();

    return 0;
}
