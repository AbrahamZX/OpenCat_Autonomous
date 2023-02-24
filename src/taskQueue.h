#include "QList/QList.h"
long taskTimer = 0;
long taskInterval = -1;
class Task {
public:
  char tkn;
  char* parameters;
  int paraLength;
  int dly;
  Task(char t, const char* p, int d = 0)
    : tkn{ t }, dly{ d } {
    paraLength = (tkn < 'a') ? strlenUntil(p, '~') : strlen(p);
    parameters = new char[paraLength + 1];
    arrayNCPY(parameters, p, paraLength);
    // for (int i = 0; i < paraLength; i++)
    //   parameters[i] = p[i];
    parameters[paraLength] = '\0';
  };
  ~Task() {
    delete[] parameters;
  };
};

class TaskQueue : public QList<Task* > {
public:
  TaskQueue() {
    PTLF("TaskQ");
  };
  // void createTask() {  //this is an example task
  //   this->push_back(new Task('k', "vtF", 2000));
  //   this->push_back(new Task('k', "up"));
  // }
  void popTask() {
    if (taskInterval == -1 || millis() - taskTimer > taskInterval) {
      Task* t = this->front();
      // PT("task: ");
      PT(t->tkn);
      // PT('\t');
      PT(t->parameters);
      // PT('\t');
      // PTL(t->dly);
      this->pop_front();
      token = t->tkn;
      lowerToken = tolower(token);
      cmdLen = t->paraLength;
      taskInterval = t->dly;
      bufferPtr = (token == T_SKILL || lowerToken == T_INDEXED_SIMULTANEOUS_ASC || lowerToken == T_INDEXED_SEQUENTIAL_ASC) ? (int8_t*)newCmd : dataBuffer;
      arrayNCPY(bufferPtr, t->parameters, cmdLen);
      bufferPtr[cmdLen] = '\0';
      taskTimer = millis();
      newCmdIdx = 5;
      delete t;
    }
  }
};
TaskQueue* tQueue;
