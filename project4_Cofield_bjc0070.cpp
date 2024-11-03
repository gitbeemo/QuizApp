#include <iostream>

using namespace std;

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* name */
struct Choice {
	string text;
	Choice* next;
};

struct Question {
	string type; // question type
	string question;
	string correctAnswer;
	double pointValue;
	Choice* choices;
};

struct Node {
	Question question;
	Node* next;
};

Choice* createChoice(const std::string& choiceText) {
	Choice* newChoice = new Choice;
	newChoice->text = choiceText;
	newChoice->next = nullptr;
	return newChoice;
}


void addChoice (Question& q) {
	string choiceText;
	for (int i = 0; i < 10; ++i) {
		cout << "Enter choice " << char('A' + i) << ": ";
		getline(cin, choiceText);
		if (choiceText == "quit()") {
			break;
		}
		Choice* newChoice = createChoice(choiceText);

		newChoice -> next = q.choices;
		q.choices = newChoice;
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to add a question to linked list */
void addQuestion (Node*& head) {
	Question q;
	q.choices = nullptr; // init the choices ptr

	// Prompt user type of question
	while (true) {
		cout << "Type of question [mcq/tf/wr]: ";
		cin >> q.type;

		if (q.type == "mcq" || q.type == "tf" || q.type == "wr") {
			break;
		} else {
			cout << "[Command not recognized, please try again!]\n\n";
		}
	}
	cin.ignore();

	cout << "Enter a question: ";
	cin >> q.question;
	getline(cin, q.question);

	if (q.type == "mcq") {
		addChoice(q);
	} else if (q.type == "tf") {

	} else if (q.type == "wr") {
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Main Function */
int main () {
	Node* head = nullptr; // init the node ptr
	char userContinueInput;

	cout << "*** Welcome to Ben's Testing Service ***\n\n";

	do {
		addQuestion(head);
		cout << "Question saved. Continue? [y/n]: ";
		cin >> userContinueInput;
	} while (tolower(userContinueInput)=='y');


}