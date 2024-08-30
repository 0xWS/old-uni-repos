import { Injectable } from '@angular/core';
import { BehaviorSubject, lastValueFrom } from 'rxjs'; // For reactive data management
import { WeatherService } from '../weather/weather.service';
import { WeatherResponse } from '../weather/weather.types';

export interface ITodo {
  title: string;
  description?: string;  // Optional description
  done: boolean;
  weather?: any;
}

@Injectable({
  providedIn: 'root' // Makes it available app-wide
})
export class TodoService {
  private todosSubject = new BehaviorSubject<ITodo[]>([]); // BehaviorSubject for updates
  todos$ = this.todosSubject.asObservable(); // Exposed as an observable

  constructor(private weatherService: WeatherService) { 
    // Load initial todos (e.g., from local storage)
    const storedTodos = localStorage.getItem('todos');
    if (storedTodos) {
      this.todosSubject.next(JSON.parse(storedTodos));
    }
  }

  addTodo(title: string, description?: string) {
    const weather: WeatherResponse = {} as WeatherResponse;
    this.weatherService.getCurrentWeather('Gdansk').subscribe((response: WeatherResponse) => {
      console.log(response);
      const newTodo: ITodo = {
        title,
        description,
        done: false,
        weather:response.current.temperature_2m,
      }
      const updatedTodos = [...this.todosSubject.value, newTodo];
      this.updateTodos(updatedTodos);
    });
    //const newTodo: ITodo = { title, description, done: false, weather: lastValueFrom(this.weatherService.getCurrentWeather('Gdańsk')).current.temperature_2m};
    //const updatedTodos = [...this.todosSubject.value, newTodo];
    //this.updateTodos(updatedTodos);
  }

  toggleTodo(index: number) {
    const updatedTodos = [...this.todosSubject.value];
    updatedTodos[index].done = !updatedTodos[index].done;
    this.updateTodos(updatedTodos);
  }

  removeTodo(index: number) {
    const updatedTodos = this.todosSubject.value.filter((_, i) => i !== index);
    this.updateTodos(updatedTodos);
  }

  private updateTodos(todos: ITodo[]) {
    this.todosSubject.next(todos); // Update the BehaviorSubject
    localStorage.setItem('todos', JSON.stringify(todos)); // Persist to local storage
  }
}