#include "Cello.h"

// インターフェイスの定義
class {
    void (*introduce)(var);
    var (*get_name)(var);
} HumanBehavior;
void introduce(var self) {
    return type_class_method(type_of(self), HumanBehavior, introduce, self);
}
var get_name(var self) {
    return type_class_method(type_of(self), HumanBehavior, get_name, self);
}

// データ型の定義
global var Human;

data {
  var type;
  var name;
} HumanData;

// メンバ関数の定義
var Human_New(var self, var_list vl);
var Human_Delete(var self);
size_t Human_Size(void);

void Human_Assign(var self, var obj);
var Human_Copy(var self);

var Human_Eq(var self, var obj);

int Human_Show(var self, var output, int pos);
int Human_Look(var self, var input, int pos);

void Human_Introduce(var self);
var Human_GetName(var self);

instance(Human, New) = { Human_New, Human_Delete, Human_Size };
instance(Human, Assign) = { Human_Assign };
instance(Human, Copy) = { Human_Copy };
instance(Human, Eq) = { Human_Eq };
instance(Human, Show) = { Human_Show, Human_Look };
instance(Human, HumanBehavior) = { Human_Introduce, Human_GetName };

var Human = type_data {
  type_begin(Human),
  type_entry(Human, New),
  type_entry(Human, Assign),
  type_entry(Human, Copy),
  type_entry(Human, Eq),
  type_entry(Human, Show),
  type_entry(Human, HumanBehavior),
  type_end(Human)
};

var Human_New(var self, var_list vl) {
  HumanData* v = cast(self, Human);
  v->name = var_list_get(vl);
  return self;
}

var Human_Delete(var self) {
  return self;
}

size_t Human_Size(void) {
  return sizeof(HumanData);
}

void Human_Assign(var self, var obj) {
  HumanData* v1 = cast(self, Human);
  HumanData* v2 = cast(obj, Human);
  v1->name = v2->name;
}

var Human_Copy(var self) {
  HumanData* v = cast(self, Human);
  return new(Human, v->name);
}

var Human_Eq(var self, var obj) {
  HumanData* v1 = cast(self, Human);
  HumanData* v2 = cast(obj, Human);
  return eq(v1->name, v2->name);
}

int Human_Show(var self, var output, int pos) {
  HumanData* v = cast(self, Human);
  return print_to(output, pos, "(%s)", v->name);
}

int Human_Look(var self, var input, int pos) {
  HumanData* v = cast(self, Human);
  var name = $(String, "");
  pos = scan_from(input, pos, "(%s)", name);
  v->name = name;
  return pos;
}

void Human_Introduce(var self) {
  HumanData* v = cast(self, Human);
  println("My name is %s.", v->name);
}

var Human_GetName(var self) {
    HumanData *v = cast(self, Human);
    return v->name;
}


// 人物の比較
void compare_human(var h1, var h2) {
    if (eq(h1, h2)) {
        println("%s is %s", get_name(h1), get_name(h2));
    } else {
        println("%s is not %s", get_name(h1), get_name(h2));
    }
}

int main(int argc, char** argv) {
    var john = new(Human, $(String, "John Doe"));
    introduce(john);
    show(john);
    println("");

    var someone1 = new(Human, $(String, "John Toe"));
    var someone2 = new(Human, $(String, "John Doe"));

    compare_human(someone1, john);
    compare_human(someone2, john);

    delete(john);
    delete(someone1);
    delete(someone2);

    return 0;
}
