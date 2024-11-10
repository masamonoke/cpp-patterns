#include <string>

class person_address_builder;
class person_job_builder;
class person_builder;

class person {
	public:
		static person_builder create();

	private:
		std::string address_;
		std::string city_;
		std::string postcode_;
		int age_{};
		int earning_{};

		friend class person_address_builder;
		friend class person_job_builder;
};

class person_builder_base {
	public:
		person_builder_base(std::unique_ptr<person> person) : person_(std::move(person)) {}

		std::unique_ptr<person> build() { return std::move(person_); }

		person_address_builder lives();
		person_job_builder works();

	protected:
		std::unique_ptr<person> person_;
};

class person_builder : public person_builder_base {
	public:
		person_builder() : person_builder_base(std::make_unique<person>()) {}
};

class person_address_builder : public person_builder_base {

	using self = person_address_builder;

	public:
		person_address_builder(std::unique_ptr<person> person) : person_builder_base(std::move(person)) {}

		self& at(std::string address) {
			person_->address_ = std::move(address);
			return *this;
		}

		self& in(std::string city) {
			person_->city_ = std::move(city);
			return *this;
		}

		self& with_postcode(std::string postcode) {
			person_->postcode_ = std::move(postcode);
			return *this;
		}
};

class person_job_builder : public person_builder_base {

	using self = person_job_builder;

	public:
		person_job_builder(std::unique_ptr<person> person) : person_builder_base(std::move(person)) {}

		self& earning(int earning) {
			person_->earning_ = earning;
			return *this;
		}

		self& aged(int age) {
			person_->age_ = age;
			return *this;
		}

};

person_builder person::create() {
	return {};
}

person_address_builder person_builder_base::lives() {
	return { std::move(person_) };
}

person_job_builder person_builder_base::works() {
	return { std::move(person_) };
}

int main() {

	auto p = person::create()
		.lives()
		.at("123 London Road")
		.in("London")
		.with_postcode("SW1A 1AA")
		.works()
		.earning(10000)
		.aged(30)
		.build();

	return 0;
}
