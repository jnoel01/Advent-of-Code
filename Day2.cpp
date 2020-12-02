
/*The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day. "Something's wrong with our computers; 
we can't log in!" You ask if you can take a look.Their password database seems to be a little corrupted: some of the
passwords wouldn't have been allowed by the Official Toboggan Corporate Policy that was in effect when they were chosen.
To try to debug the problem, they have created a list (your puzzle input) of passwords (according to the corrupted database)
and the corporate policy when that password was set. Each line gives the password policy and then the password. The password
policy indicates the lowest and highest number of times a given letter must appear for the password to be valid. For example,
1-3 a means  that the password must contain a at least 1 time and at most 3 times.

How many passwords are valid in the input? */

struct ValidPW {
private:
  int low;
  int high;
  char target;
  std::string password;

public:
  static std::vector<std::string> parse(std::string &input) {
    std::vector<std::string> parts;
    std::string curPart;

    for (char c : input) {
      if ((c == ' ' || c == '-' || c == ':') && curPart.length()) {
        parts.push_back(curPart);
        curPart.clear();
      } else {
        curPart += c;
      }
    }

    parts.push_back(curPart);
    return parts;
  }

  bool valid() {
    return (this->password[low] == target) != (this->password[high] == target) ;
  }

  ValidPW(std::string &input) {
    std::vector<std::string> parts = ValidPW::parse(input);
    low = std::stoi(parts[0]);
    high = std::stoi(parts[1]);
    target = parts[2][0]; // always a single char
    password = parts[3];
  }
};

int main() {
  std::fstream newfile;
  int passwordCount = 0;

  newfile.open("input.txt", std::ios::in);

  if (newfile.is_open()) {
    std::string line;

    while(getline(newfile, line)) {
      passwordpw(line);
      if (pw.valid()) passwordCount++;
    }

    newfile.close();
  }

  std::cout << passwordCount << std::endl;

  return 0;
}