#include <iostream>
#include <set>
#include <vector>

struct Segment {
  size_t left_border;
  size_t length;
  Segment* prev;
  Segment* next;
  bool is_busy;
};

class Allocator {
 private:
  size_t n_;
  Segment* head_;
  std::vector<Segment*> queries_;
  std::set<std::tuple<size_t, long long, Segment*>,
           std::greater<std::tuple<size_t, long long, Segment*>>>
      free_memory_;

 public:
  Allocator(size_t n)
      : n_(n), head_(new Segment{0, n_, nullptr, nullptr, false}) {
    free_memory_.insert({n_, 0, head_});
  }

  void Allocate(size_t k) {
    if (free_memory_.empty()) {
      queries_.push_back(nullptr);
      std::cout << "-1\n";
      return;
    }
    // Получаем из сета итератор на (размер макс. сегмента, -левая граница,
    // указатель на него)
    auto it_max_segment = free_memory_.begin();
    // Если длина сегмента меньше k, ничего не делаем
    if (std::get<0>(*it_max_segment) < k) {
      queries_.push_back(nullptr);
      std::cout << "-1\n";
      return;
    }
    // Иначе сегмент надо достать из сета, запомнив указатель на него
    Segment* to_busy = std::get<2>(*it_max_segment);
    std::cout << to_busy->left_border + 1 << "\n";
    free_memory_.erase(it_max_segment);
    // Если при это длина сегмента ровно k, то нам нужно лишь пометить его
    // занятым и отправить в массив queries указатель на него
    if (to_busy->length == k) {
      to_busy->is_busy = true;
      queries_.push_back(to_busy);
      return;
    }
    // Если же длина сегмента больше k, то разбиваем его на 2 сегмента
    Segment* free_piece =
        new Segment{to_busy->left_border + k, to_busy->length - k, to_busy,
                    to_busy->next, false};
    to_busy->length = k;
    to_busy->next = free_piece;
    if (free_piece->next != nullptr) {
      free_piece->next->prev = free_piece;
    }
    to_busy->is_busy = true;
    // Теперь в вектор пихаем указатель на занятый сегмент,
    // а в сет длину и указатель на свободный
    queries_.push_back(to_busy);
    free_memory_.insert({free_piece->length,
                         -((long long)(free_piece->left_border)), free_piece});
  }

  void Deallocate(size_t q) {
    queries_.push_back(nullptr);
    // Ищем в векторе queries указатель на соответствующий сегмент
    Segment* to_free = queries_[q];
    queries_[q] = nullptr;
    // Если на k-том запросе не происходило выделения памяти, ничего не делаем
    if (to_free == nullptr) {
      return;
    }
    // Помечаем сегмент как свободный и смотрим на его соседей
    // Если они есть и свободны - сливаем
    // Не забываем обновить их длины в сете
    to_free->is_busy = false;
    // Если оба свободны
    if (to_free->prev != nullptr && !to_free->prev->is_busy &&
        to_free->next != nullptr && !to_free->next->is_busy) {
      auto it_of_prev = free_memory_.find(
          {to_free->prev->length, -((long long)(to_free->prev->left_border)),
           to_free->prev});
      free_memory_.erase(it_of_prev);
      to_free->prev->length += to_free->length + to_free->next->length;
      free_memory_.insert({to_free->prev->length,
                           -((long long)(to_free->prev->left_border)),
                           to_free->prev});
      free_memory_.erase({to_free->next->length,
                          -((long long)(to_free->next->left_border)),
                          to_free->next});
      to_free->prev->next = to_free->next->next;
      if (to_free->next->next != nullptr) {
        to_free->next->next->prev = to_free->prev;
      }
      delete to_free->next;
      delete to_free;
      return;
    }
    // Если свободен только следующий
    if (to_free->next != nullptr && !to_free->next->is_busy) {
      auto it_of_next = free_memory_.find(
          {to_free->next->length, -((long long)(to_free->next->left_border)),
           to_free->next});
      free_memory_.erase(it_of_next);
      to_free->next->left_border = to_free->left_border;
      to_free->next->length += to_free->length;
      free_memory_.insert({to_free->next->length,
                           -((long long)(to_free->next->left_border)),
                           to_free->next});
      to_free->next->prev = to_free->prev;
      if (to_free->prev != nullptr) {
        to_free->prev->next = to_free->next;
      }
      if (to_free == head_) {
        head_ = to_free->next;
      }
      delete to_free;
      return;
    }
    // Если свободен только предыдущий
    if (to_free->prev != nullptr && !to_free->prev->is_busy) {
      auto it_of_prev = free_memory_.find(
          {to_free->prev->length, -((long long)(to_free->prev->left_border)),
           to_free->prev});
      free_memory_.erase(it_of_prev);
      to_free->prev->length += to_free->length;
      free_memory_.insert({to_free->prev->length,
                           -((long long)(to_free->prev->left_border)),
                           to_free->prev});
      to_free->prev->next = to_free->next;
      if (to_free->next != nullptr) {
        to_free->next->prev = to_free->prev;
      }
      delete to_free;
      return;
    }
    // Иначе просто пихаем в free_memory
    free_memory_.insert(
        {to_free->length, -((long long)((to_free->left_border))), to_free});
  }

  ~Allocator() {
    while (head_ != nullptr) {
      Segment* to_delete = head_;
      head_ = head_->next;
      delete to_delete;
    }
  }
};

int main() {
  freopen("input.txt", "r", stdin);

  size_t n;
  size_t q;
  std::cin >> n >> q;

  Allocator allocator(n);
  for (size_t i = 0; i < q; i++) {
    long long k;
    std::cin >> k;
    if (k > 0) {
      allocator.Allocate((size_t)k);
    } else {
      allocator.Deallocate((size_t)(-k - 1));
    }
  }
}