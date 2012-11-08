struct sell_order {
  int price;
  int *num;
};

bool operator==(const sell_order& so1, const sell_order& so2) {
  return so1.price==so2.price;
}
bool operator<(const sell_order& so1, const sell_order& so2) {
  return so1.price>so2.price;
}
