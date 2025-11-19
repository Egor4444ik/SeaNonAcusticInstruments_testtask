#include <iostream>
#include <vector>

struct Sample {
    int x;
    int y;
};

std::vector<Sample> thinSequence(const std::vector<Sample>& seq, int n) {
    std::vector<Sample> result;

    if (seq.empty()) {
        return result;
    }

    int sample_index = 0;
    int size = static_cast<int>(seq.size());

    while (sample_index < size) {
        int start = sample_index;
        int currentY = seq[sample_index].y;

        // Находим конец текущего блока с одинаковым y
        int end = start;
        while (end + 1 < size && seq[end + 1].y == currentY) {
            ++end;
        }

        // Теперь блок — это элементы с индексами [start, end]
        int len = end - start + 1;

        // Проходим по блоку и выбираем нужные элементы
        for (int k = 0; k < len; ++k) {
            int localIndex = k + 1; // Нумерация внутри блока: (1,...,len)

            if (localIndex == 1 ||            
                localIndex == len ||         
                (localIndex % n == 0))    
            {
                result.push_back(seq[start + k]);
            }
        }

        sample_index = end + 1;
    }

    return result;
}

// Печать последовательности в виде (x, y)
void printSequence(const std::vector<Sample>& seq) {
    for (const auto& s : seq) {
        std::cout << "(" << s.x << ", " << s.y << ") ";
    }
    std::cout << std::endl;
}

int main() {
    int N;
    std::cout << "Введите количество элементов: ";
    std::cin >> N;

    std::vector<Sample> data(N);

    std::cout << "Введите " << N << " пар значений X Y:\n";
    for (int i = 0; i < N; ++i) {
        std::cin >> data[i].x >> data[i].y;
    }

    int n;
    std::cout << "Введите n (каждый n-й элемент сохраняется): ";
    std::cin >> n;

    std::cout << " Исходная последовательность:\n";
    printSequence(data);

    std::cout << "\n Результат при n = " << n << ":\n";

    auto thinned = thinSequence(data, n);
    printSequence(thinned);

    return 0;
}
