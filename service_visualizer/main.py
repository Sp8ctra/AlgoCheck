import random
import requests
from fastapi import FastAPI

app = FastAPI()
CPP_SERVICE_URL = "http://service_analyzer:8080/analyze"

@app.get("/")
def home():
    return {"message": "Микросервис тестирования C++ алгоритмов"}

@app.get("/run_experiment")
def run_experiment():
    results = []
    # Размеры массивов для проверки сложности алгоритма
    sizes = [100, 500, 1000, 2000]

    for size in sizes:
        # Генерация случайных чисел
        random_array = [random.randint(1, 10000) for _ in range(size)]
        try:
            # Отправка массива в С++ контейнер
            response = requests.post(CPP_SERVICE_URL, json={"data": random_array}, timeout=10)
            data = response.json()
            results.append({
                "N_elements": size,
                "time_microseconds": data["execution_time_us"]
            })
        except Exception as e:
            return {"error": f"Ошибка связи с C++: {str(e)}"}

    return {
        "status": "Эксперимент завершен",
        "algorithm": "Bubble Sort (C++)",
        "complexity_data": results
    }
