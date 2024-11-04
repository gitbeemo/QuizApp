#include <algorithm>
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
/* Function to check correct answer for MCQ */
bool isCorrectAnswer(Question& q, const string& correctAnswer) {
	Choice* current = q.choices;
	char correctChar = tolower(correctAnswer[0]);
	char allowedChar = 'a';
	while (current != nullptr) {
		if (correctChar == allowedChar) return true;
		current = current->next;
		++allowedChar;
	}
	return false;
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
	cout << "[At any time, type 'quit()' to exit]\n";
	getline(cin, q.question);

	if (q.type == "mcq") {
		addChoice(q);
		while (true) {
			cout << "Select correct answer: ";
			cin >> q.correctAnswer;
			transform(q.correctAnswer.begin(), q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);

			if (isCorrectAnswer(q, q.correctAnswer)) {
				break;
			}
			cout << "[Answer not recognized, please try again!]\n";
		}

	} else if (q.type == "tf") {
		while (true) {
			cout << "Select correct answer: ";
			cin >> q.correctAnswer;
			transform(q.correctAnswer.begin(),q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);
			if (q.correctAnswer == "true" || q.correctAnswer == "false") {
				break;

			}
			cout << "[Answer not recognized, please try again!]\n";
		}
	} else if (q.type == "wr") {
		cout << "Type correct answer: ";
		cin.ignore();
		getline(cin, q.correctAnswer);
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