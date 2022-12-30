//-- Includes i o Library
# include <iostream>
# include <vector>
# include <cmath>

//-- Compile Time Definitions
enum SortAlgorithms {
    Bubble,
    Insertion,
    Selection
};

//-- Polynode Class
class Polynode {
    private:
        //-- Coefficient
        int coef;
        //-- Exponent
        int exp;
    public:
        //-- Default Constructor
        Polynode();
        //-- Parameteric Constructor
        Polynode(int &, int &);
        //-- Polynode's Exponant Returner
        int getExp();
        //-- Set Exponent of Polynode
        void setExp(int &);
        //-- Polynode's Coefficient Returner
        int getCoef();
        //-- Set Coefficient of Polynode
        void setCoef(int &);
        //-- Output Stream Operator
        friend std::ostream &operator << (std::ostream &, Polynode &);
        //-- Input Stream Operator
        friend std::istream &operator >> (std::istream &, Polynode &);
        //-- Relational Operator
        bool operator == (const Polynode &) const;
        //-- Arithmetic Operator
        Polynode operator + (Polynode &);
        //-- Assignment Operator
        Polynode operator = (Polynode &);
};

//-- Polynomial Class
class Polynomial : public Polynode {
    private:
        //-- Creates Phrase of Polynodes
        std::vector <Polynode> phrase;
        //-- Shows Number of Polynodes in Polynomial
        int size;
        //-- Swap Two Polynodes
        void Swap(Polynode &, Polynode &);
    public:
        //-- Default Constructor
        Polynomial();
        //-- Parametric Constructor
        Polynomial(std::vector<Polynode> &, int &);
        //-- Append Polynode to Polynomial
        void Append(Polynode &);
        //-- Calculates Polynomial with Given Input
        int calculateWith(double &);
        //-- Sort Polynodes According to Their Exponant
        void Sort(int);
        //-- Returns Maximum Avalible Term in Polynomial
        Polynode maxTerm();
        //-- Returns Maximum Avalible Exponant in Polynomial
        int maxExp();
        //-- Phrase Size Returner
        int getSize();
        //-- Output Stream Operator
        friend std::ostream &operator << (std::ostream &, Polynomial &);
        //-- Input Stream Operator
        friend std::istream &operator >> (std::istream &, Polynomial &);
        //-- Arithmetic Operator
        Polynomial operator + (Polynomial &);
};

//--------------------------------------------------------------------------------------------
//----------------------------------------- Polynode -----------------------------------------
//--------------------------------------------------------------------------------------------

//-- Default Constructor
Polynode::Polynode() {
    coef = 0;
    exp = 0;
    
}

//-- Parameteric Constructor
Polynode::Polynode(int &inputCoef, int &inputExp) {
    coef = inputCoef;
    exp = inputExp;
}

//-- Polynode's Exponant Returner
int Polynode::getExp() {
    return exp;
}

//-- Set Exponent of Polynode
void Polynode::setExp(int &input) {
    if (input > 0 || input < 0) {
        exp = input;
    } else {
        exp = 1;
    }
}

//-- Polynode's Coefficient Returner
int Polynode::getCoef() {
    return coef;
}

//-- Set Coefficient of Polynode
void Polynode::setCoef(int &input) {
    coef = input;
}

//-- Output Stream Operator
std::ostream &operator << (std::ostream &output, Polynode &polynode) {
    if (polynode.getCoef() == 0) {
        output << "0";
    } else if (polynode.getCoef() == 1) {
        if (polynode.getExp() == 0) {
            output << polynode.getCoef(); 
        } else if (polynode.getExp() == 1) {
            output << "x";
        } else {
            output << "x^" << polynode.getExp();
        }
    } else {
        if (polynode.getExp() == 0) {
            output << polynode.getCoef(); 
        } else if (polynode.getExp() == 1) {
            output << polynode.getCoef() << "x";
        } else {
            output << polynode.getCoef() << "x^" << polynode.getExp();
        }
    }
    return output;
}

//-- Input Stream Operator
std::istream &operator >> (std::istream &input, Polynode &polynode) {
    int _coef, _exp;
    std::cout << "- Enter Coefficient of Polynode : ";
    input >> _coef;
    std::cout << "- Enter Exponant of Polynode : ";
    input >> _exp;
    polynode.setCoef(_coef);
    polynode.setExp(_exp);
    std::cout << "-- (" << polynode << ") Has been Added !" << std::endl; 
    return input;
}

//-- Relational Operator
bool Polynode::operator == (const Polynode &rvalue) const {
    if (rvalue.coef == this->coef && rvalue.exp == this->exp) {
        return true;
    }
    return false;
}

//-- Arithmetic Operator
Polynode Polynode::operator + (Polynode &rvalue) {
    if (rvalue.exp == this->exp) {
        this->coef += rvalue.coef;
    } else {
        std::cout << "Exponants are Different ! Can't Do Arithmetic Operation." << std::endl;
    }
    return *this;
}

//-- Assignment Operator
Polynode Polynode::operator = (Polynode &rvalue) {
    this->coef = rvalue.coef;
    this->exp = rvalue.exp;
}

//--------------------------------------------------------------------------------------------
//---------------------------------------- Polynomial ----------------------------------------
//--------------------------------------------------------------------------------------------

//-- Swap Two Polynodes
void Polynomial::Swap(Polynode &polynode1, Polynode &polynode2) {
    Polynode tmp;
    tmp = polynode2;
    polynode2 = polynode1;
    polynode1 = tmp;
}

//-- Default Constructor
Polynomial::Polynomial() {
    phrase.resize(0);
    size = 0;
}

//-- Parametric Constructor
Polynomial::Polynomial(std::vector<Polynode> &inputPhrase, int &inputSize) {
    phrase.resize(inputPhrase.size());
    for (int i = 0; i < phrase.size(); i++) {
        phrase.push_back(inputPhrase[i]);
        size = i;
    }
}

//-- Append Polynode to Polynomial
void Polynomial::Append(Polynode &input) {
    std::cin >> input;
    phrase.push_back(input);
    size = phrase.size();
    Sort(Bubble);
}

//-- Calculates Polynomial with Given Input
int Polynomial::calculateWith(double &input) {
    if (phrase.size() == 0) {
        std::cout << "Polynomial is Empty : ";
        return 0;
    }
    double answer = 0;
    for (int i = 0; i < phrase.size(); i++) {
        answer += (phrase[i].getCoef() * pow(input, phrase[i].getExp()));
    }
    return answer;
}

//-- Sort Polynodes According to Their Exponant
void Polynomial::Sort(int algorithm) {
    switch (algorithm) {
        //-- Bubble Sort Algorithm
        case Bubble: {
            for (int i = 0; i < phrase.size() - 1; i++) {
                for (int j = 0; j < phrase.size() - 1; j++) {
                    if (phrase[j + 1].getExp() > phrase[j].getExp()) {
                        Swap(phrase[j], phrase[j + 1]);
                    } else if (phrase[j + 1].getExp() == phrase[j].getExp()) {
                        if (phrase[j + 1].getCoef() > phrase[j].getCoef()) {
                            Swap(phrase[j + 1], phrase[j]);
                        }
                    }
                }
            }
            break;
        };
        //-- Insertion Sort Algorithm
        case Insertion: {
            int j;
            Polynode tmp;
            for (int i = 1; i < phrase.size(); i++) {
                tmp = phrase[i];
                j = i - 1;
                while (phrase[i + 1].getExp() > phrase[i].getExp()) {
                    Swap(phrase[j + 1], phrase[j]);
                    j--;
                }
                while (phrase[i + 1].getExp() == phrase[i].getExp()) {
                    if (phrase[j + 1].getCoef() > phrase[j].getCoef()) {
                        Swap(phrase[j + 1], phrase[j]);
                    }
                }
                phrase[j + 1] = tmp;
            }
            break;
        };
        //-- Selection Sort Algorithm
        case Selection: {
            int level = 0;
            for (int i = 0; i < phrase.size() - 1; i++) {
                level = i;
                for (int j = i + 1; j < phrase.size(); j++) {
                    if (phrase[level].getExp() > phrase[j].getExp()) {
                        level = j;
                    } else if (phrase[level].getExp() == phrase[j].getExp()) {
                        if (phrase[level].getCoef() > phrase[j].getCoef()) {
                            level = j;
                        }
                    }
                }
                Swap(phrase[i], phrase[level]);
            }
            break;
        };
    };
}

//-- Returns Maximum Avalible Term in Polynomial
Polynode Polynomial::maxTerm() {
    Sort(Bubble);
    return phrase[0];
}

//-- Returns Maximum Avalible Exponant in Polynomial
int Polynomial::maxExp() {
    Sort(Bubble);
    return phrase[0].getExp();
}

//-- Phrase Size Returner
int Polynomial::getSize() {
    return size;
}

//-- Output Stream Operator
std::ostream &operator << (std::ostream &output, Polynomial &polynomial) {
    bool flag = false;
    for (int i = 0; i < polynomial.phrase.size(); i++) {
        if (polynomial.phrase[i].getCoef() > 0 && i > 0) {
            output << " + ";
            flag = true;
        } else if (polynomial.phrase[i].getCoef() < 0) {
            output << " ";
            flag = true;
        } else if (polynomial.phrase[i].getCoef() == 0) {
            //-- Doesn't Show Polynode
            flag = false;
        }
        if (flag == true) {
            output << polynomial.phrase[i];
        }
    }
    return output;
}

//-- Input Stream Operator
std::istream &operator >> (std::istream &input, Polynomial &polynomial) {
    // polynomial.phrase[0].
    // std::cout << "aaaa" << std::endl;
}

//-- Arithmetic Operator
Polynomial operator + (Polynomial &rvalue) {
    // return *this;
}

//-- Main
int main() {
    //-- Menu
    Polynomial phrase;
    //-- flag
    bool wrongOption = false;
    bool continueChoice = true;
    while (true) {
        //-- Wrong Option Process
        if (wrongOption == true) {
            //-- Clear Terminal
            std::cout << "\x1B[2J\x1B[H" << std::endl;
            std::cout << "--- Wrong Option ! Enter Your Choice Again !" << std::endl;
            wrongOption = false;
        } else {
            //-- Clear Terminal
            std::cout << "\x1B[2J\x1B[H" << std::endl;
            std::cout << std::endl;
        }
        //-- Show Polynomial Status
        if (phrase.getSize() == 0) {
            std::cout << "Your Polynode is Empty !" << std::endl;
        } else {
            std::cout << "Your Polynomial has \033[0;33m" << phrase.getSize() << "\033[0m Polynodes." << std::endl;
        }
        //-- Options :
        std::cout << "Options :" << std::endl;
        //-1 : Add Polynode
        std::cout << "1- Add Polynode" << std::endl;
        //-2: Calculates Polynomial with Given Input
        std::cout << "2- Calculates Polynomial with Given Input" << std::endl;
        //-3 : Show Sorted Polynomial
        std::cout << "3- Show Sorted Polynomial" << std::endl;
        //-4 : Show Biggest Term
        std::cout << "4- Show Biggest Term in Polynomial" << std::endl;
        //-5 : Show Polynomial's Degree
        std::cout << "5- Show Polynomial's Degree" << std::endl;
        //-- Choice
        int choice = 0;
        std::cout << std::endl << "Your Choice : "; std::cin >> choice;
        switch (choice) {
            case 1: {
                Polynode input;
                phrase.Append(input);
                break;
            };
            case 2: {
                double input;
                phrase.Sort(Bubble);
                std::cout << "- Enter Input : "; std::cin >> input;
                std::cout << "  x = " << input << " --> " << phrase << std::endl;
                std::cout << "-- Answer : " << phrase.calculateWith(input) << std::endl;
            };
            case 3: {
                phrase.Sort(Bubble);
                std::cout << phrase << std::endl;
                break;
            };
            case 4: {
                phrase.Sort(Bubble);
                
                break;
            };
            case 5: {
                phrase.Sort(Bubble);
                std::cout << "Polynomial's Degree is : " << phrase.getExp();
                break;
            };
            default: {
                wrongOption = true;
            };
        };
        // std::cout << "Polynomial is : " << phrase << std::endl;
        if (wrongOption == false) {
            std::string input;
            while (true) {
                std::cout << "Continue ? (Y/N) : "; std::cin >> input;
                if (input == "y" || input == "Y") {
                    continueChoice = true;
                    break;
                } else if (input == "n" || input == "N"){
                    continueChoice = false;
                    break;
                } else {
                    std::cout << "- Wrong Answer !" << std::endl;
                }
            }
            if (continueChoice == true) {
                continue;
            } else {
                break;
            }
        }
    }
    std::cout << std::endl;
    std::cout << "Program Terminated Successfully." << std::endl;    
}