#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

const int cOne = 123;
const int cTwo = 45;
const int cThree = 10'004'321;

int Partition(std::vector<int>& a, int n, int pivot) {
  // Ищем индекс пивота
  int id_pivot = 0;
  for (int i = 0; i < n; i++) {
    if (pivot == a[i]) {
      id_pivot = i;
      break;
    }
  }
  // Ставим пивот на первое место
  std::swap(a[0], a[id_pivot]);
  // Начинаем Partition:
  // Поддерживаем указатель на последний <= элемент
  // И указатель на проверяемый элемент
  // Если проверяемый элемент <=, свопаем с элементом за границей
  // Расширяем границу
  // Иначе - скип
  int last_not_greater = 0;
  for (int i = 1; i < n; i++) {
    if (a[i] <= pivot) {
      std::swap(a[i], a[last_not_greater + 1]);
      last_not_greater++;
    }
  }
  std::swap(a[last_not_greater], a[0]);
  return last_not_greater;
}

int DQSel(std::vector<int>& a, int n, int k) {
  // Если длина массива меньше 5, просто сортируем его
  // и возвращаем, что нужно
  if (a.size() <= 5) {
    std::sort(a.begin(), a.end());
    return a[k];
  }
  // Если больше 5, то делим на массивы по <= 5
  // И ищем в них медианы
  std::vector<int> medians;
  int i = 0;
  int j = 0;
  while (i + 5 < n) {
    i += 5;
    std::vector<int> sub_a(a.begin() + j, a.begin() + i);
    medians.push_back(DQSel(sub_a, 5, 2));
    j += 5;
  }
  // Чтобы не хранить далее sub_a и его зарактеристики
  // Откроем новую область видимости
  {
    std::vector<int> sub_a(a.begin() + i, a.end());
    int nsa = sub_a.size();
    int ksa = nsa / 2;
    medians.push_back(DQSel(sub_a, nsa, ksa));
  }
  // Массив медиан заполнен, ищем в нем медиану
  int pivot = DQSel(medians, medians.size(), medians.size() / 2);
  // Далее, запускаем Partition и простая рекурсия
  int id_of_sorted_pivot = Partition(a, n, pivot);
  if (id_of_sorted_pivot == k) {
    return a[id_of_sorted_pivot];
  }
  if (id_of_sorted_pivot > k) {
    std::vector<int> cut_a(a.begin(), a.begin() + id_of_sorted_pivot);
    return DQSel(cut_a, cut_a.size(), k);
  }
  std::vector<int> cut_a(a.begin() + id_of_sorted_pivot, a.end());
  return DQSel(cut_a, cut_a.size(), k - id_of_sorted_pivot);
}

int main() {
  std::ifstream fin;
  fin.open("input.txt");

  int n;
  int k;
  int a0;
  int a1;
  fin >> n >> k >> a0 >> a1;
  k--;
  std::vector<int> a(n);
  a[0] = a0;
  a[1] = a1;
  for (int i = 2; i < n; i++) {
    a[i] = (a[i - 1] * cOne % cThree + a[i - 2] * cTwo % cThree) % cThree;
  }
  std::cout << DQSel(a, n, k);
}