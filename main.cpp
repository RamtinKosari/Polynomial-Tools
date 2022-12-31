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
        Polynode operator = (const Polynode &);
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
        Polynomial(std::vector<Polynode> &, int);
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
        friend std::ostream &operator << (std::ostream &, Polynomial);
        //-- Input Stream Operator
        friend std::istream &operator >> (std::istream &, Polynomial &);
        //-- Arithmetic Operator
        Polynomial operator + (Polynomial &);
        //-- Set Polynode
        void setPolynode(int &);
        //-- Polynode's Returner
        Polynode getPolynode(int &);
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
            output << polynode.getCoef();
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
Polynode Polynode::operator = (const Polynode &rvalue) {
    this->coef = rvalue.coef;
    this->exp = rvalue.exp;
    return *this;
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
Polynomial::Polynomial(std::vector<Polynode> &inputPhrase, int inputSize) {
    size = inputSize;
    for (int i = 0; i < size; i++) {
        phrase.push_back(inputPhrase[i]);
    }
}

//-- Append Polynode to Polynomial
void Polynomial::Append(Polynode &input) {
    std::cin >> input;
    phrase.push_back(input);
    size = phrase.size();
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
        if (i > 0) {
            std::cout << " + ";
        }
        std::cout << phrase[i].getCoef() * pow(input, phrase[i].getExp());
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
    return phrase.at(0);
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
std::ostream &operator << (std::ostream &output, Polynomial polynomial) {
    bool flag = false, hasSign = false;
    int coef, size = polynomial.size;
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         if (polynomial.phrase[i].getExp() == polynomial.phrase[j].getExp()) {
    //             std::cout << polynomial.phrase[i].getCoef() << " coef " << polynomial.phrase[j].getCoef() << std::endl;
    //             std::cout << polynomial.phrase[i].getExp() << " exp " << polynomial.phrase[j].getExp() << std::endl;
    //             polynomial.phrase[i] = polynomial.phrase[i] + polynomial.phrase[j];
    //             polynomial.phrase.erase(polynomial.phrase.begin() + j);
    //             polynomial.size--;
    //             std::cout << "done : " << polynomial.phrase[i].getCoef();
    //         }
    //     }
    // }
    for (int i = 0; i < polynomial.phrase.size(); i++) {
        coef = polynomial.phrase[i].getCoef();
        if (coef > 0 && i > 0) {
            output << " + ";
            flag = true;
        } else if (coef < 0) {
            if (polynomial.maxTerm() == polynomial.phrase[i]) {
                output << "- ";
            } else {
                output << " - ";
            }
            polynomial.phrase[i].setCoef(coef *= -1);
            hasSign = true;
            flag = true;
        } else if (polynomial.phrase[i].getCoef() == 0) {
            //-- Doesn't Show Polynode
            flag = false;
        }
        if (flag == true || i == 0) {
            output << polynomial.phrase[i];
            if (hasSign) {
                polynomial.phrase[i].setCoef(coef *= -1);
                hasSign = false;
            }
        }
    }
    return output;
}

//-- Input Stream Operator
std::istream &operator >> (std::istream &input, Polynomial &polynomial) {

}

//-- Arithmetic Operator
Polynomial Polynomial::operator + (Polynomial &rvalue) {
    for (int i = 0; i < rvalue.getSize(); i++) {
        this->phrase.push_back(rvalue.phrase[i]);
    }
    return *this;
}

//-- Set POlynode
void Polynomial::setPolynode(int &index) {
    std::cin >> phrase[index];
}

//-- Polynode's Returner
Polynode Polynomial::getPolynode(int &index) {
    std::cin >> phrase[index];
    return phrase[index];
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
            std::cout << "\x1B[2J\x1B[H";
            std::cout << "\033[0;31mWrong Option !\033[0m Enter Your Choice Again !" << std::endl;
            wrongOption = false;
        } else {
            //-- Clear Terminal
            std::cout << "\x1B[2J\x1B[H";
            std::cout << std::endl;
        }
        //-- Show Polynomial Status
        if (phrase.getSize() == 0) {
            std::cout << "Your Polynode is \033[0;33mEmpty\033[0m!" << std::endl << std::endl;
        } else {
            phrase.Sort(Bubble);
            std::cout << "Your Polynomial has \033[0;33m" << phrase.getSize() << "\033[0m Polynodes." << std::endl;
            std::cout << std::endl;
        }
        //-- Options :
        std::cout << "\033[0;35mOptions :\033[0m" << std::endl;
        //-1 : Add Polynode
        std::cout << "\033[0;33m1-\033[0m Add Polynode" << std::endl;
        //-2: Calculates Polynomial with Given Input
        std::cout << "\033[0;33m2-\033[0m Calculates Polynomial with Given Input" << std::endl;
        //-3 : Show Sorted Polynomial
        std::cout << "\033[0;33m3-\033[0m Show Sorted Polynomial" << std::endl;
        //-4 : Show Biggest Term
        std::cout << "\033[0;33m4-\033[0m Show Biggest Term in Polynomial" << std::endl;
        //-5 : Show Polynomial's Degree
        std::cout << "\033[0;33m5-\033[0m Show Polynomial's Degree" << std::endl;
        //-6 : Add Two Polynomial
        std::cout << "\033[0;33m6-\033[0m Add Another Polynomial" << std::endl;
        //-7 : Set Polynode
        std::cout << "\033[0;33m7-\033[0m Set Polynode by Index" << std::endl;
        //-- Choice
        int choice = 0;
        std::cout << std::endl << "\033[0;35mYour Choice :\033[0m "; std::cin >> choice;
        if (phrase.getSize() == 0 && choice != 1) {
            std::cout << "- You Should Add at Least One Polynode" << std::endl;
            choice = 1;
        }
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
                std::cout << "-- x = " << input << " --> " << phrase << std::endl;
                std::cout << "-- Answer : " << phrase.calculateWith(input) << std::endl;
            };
            case 3: {
                phrase.Sort(Bubble);
                std::cout << "- Polynomial : " << phrase << std::endl;
                break;
            };
            case 4: {
                Polynode output;
                output = phrase.maxTerm();
                std::cout << "- Maximum Term is : " << output << std::endl;
                break;
            };
            case 5: {
                std::cout << "- Polynomial's Degree is : " << phrase.maxExp() << std::endl;
                break;
            };
            case 6: {
                std::cout << "- Add Term to New Polynomial, in The End Will be Added to Main Polynomial :" << std::endl;
                std::vector<Polynode> polynode;
                polynode.resize(0);
                bool status = true;
                std::string input;
                Polynode tmp;
                while (true) {
                    if (status == true) {
                        std::cin >> tmp;
                        polynode.push_back(tmp);
                        std::cout << "- Continue Adding ? (Y/N) : "; std::cin >> input; 
                        if (input == "y" || input == "Y") {
                            status = true; 
                        } else if (input == "n" || input == "N"){
                            status = false;
                            break;
                        }
                    }
                }
                Polynomial polynomial(polynode, polynode.size());
                phrase = phrase + polynomial;
                // std::cin >> phrase;
                break;
            };
            case 7: {
                std::cout << "- Polynomial is : " << phrase << std::endl;
                std::cout << "                    ";
                for (int i = 0; i < phrase.getSize(); i++) {
                    std::cout << i << "      ";
                }
                int index;
                std::cout << std::endl;
                std::cout << "- Choose Between Iterators : "; std::cin >> index;
                std::cout << "Polynode " << index << " is Selected" << std::endl;
                phrase.setPolynode(index);
                std::cout << "Polynode [" << index << "] Replaced Successfully !" << std::endl;
                break;
            }
            default: {
                wrongOption = true;
            };
        };
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