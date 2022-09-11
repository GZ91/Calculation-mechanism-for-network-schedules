#pragma once
#include <ctime>
#include <string>
#include <vector>
#include "nlohmann\json.hpp"
#include "task_and_type.hpp"

using json = nlohmann::json;

class Task {
public:
	explicit Task(json&);
	Task(Task&) = delete;
	Task& operator=(Task&) = delete;
	~Task();
	//void fill_time();
	unsigned long long get_key(); //возвращает ключ задачи
	std::vector<std::shared_ptr<TaskAndType>>& get_followers(); //возвращает задачи последователи
	std::vector <std::shared_ptr<TaskAndType>>& get_predecessors(); //возвращает задачи предшественники
	std::time_t get_time_end(); //вернуть время окончания задачи
	std::time_t get_time_start();  //вернуть время начала задачи
	bool set_time_end_start(std::time_t); //изменить время для типа связи старт после окончания
	bool set_time_start_start(std::time_t); //изменить время для типа связи старт после старта
	void add_followers(std::shared_ptr<TaskAndType> task); //добавить последователя
	bool its_not_prev_task(); //это задача без предшественников (задача начала графика)
private:
	unsigned long long ID; //уникальный идентификатор задачи - приходит с json
	std::string key_calendate; //код каллендаря
	bool its_critical_task; //это задача критического пути
	int NestingLevel; //уровень вложенности
	bool sum; //это суммовая задача
	std::vector <std::shared_ptr<TaskAndType>> followers; //вектор задач последователей
	std::vector <std::shared_ptr<TaskAndType>> predecessors; //вектор задач предшественников	
	std::time_t minimum_time_start_fact; //минимальное время начала фактическое
	std::time_t maximum_time_end_fact; //максимальное время окончания фактическое
	std::time_t begin_NRCH; //"начало не раньше чем"
	std::time_t second_start;//секунда старта задачи
	std::time_t second_end;//секунда окончания задачи
	std::time_t second_lendth; //длина в секундах

	void linkage_upload(json links); //загрузить связи в задачу
	void print_error(std::string text_error, int type_error = 0); //распечатать ошибку
};