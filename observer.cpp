#include <iostream>
#include <map>

struct observerable {
	virtual ~observerable() = default;

	virtual void notify() = 0;
	virtual void subscribe(const void* o, std::function<void(void)> f) = 0;
	virtual void unsubscribe(const void* o) = 0;
};

struct person : public observerable {
	public:
		int get_age() const {
			return age_;
		}

		void set_age(int age) {
			age_ = age;
			notify();
		}

		void subscribe(const void* o, std::function<void(void)> f) override {
			observers_[o] = f;
		}

		void unsubscribe(const void* o) override {
			auto it = observers_.find(o);
			if (it != observers_.end()) {
				observers_.erase(it);
			}
		}

	private:
		int age_ = 0;
		std::map<const void*, std::function<void(void)>> observers_;

		void notify() override {
			for (auto &kv : observers_) {
				kv.second();
			}
		}
};

int main() {
	person p;
	int id = 1;

	auto f = [&p]() { std::cout << p.get_age() << "\n"; };
	p.subscribe(&id, f);
	p.set_age(21);
	p.set_age(22);
	p.unsubscribe(&id);
	p.set_age(23);

	return 0;
}
