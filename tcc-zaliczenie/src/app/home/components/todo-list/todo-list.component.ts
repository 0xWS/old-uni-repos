import { Component, OnInit } from '@angular/core';
import {MatListModule} from '@angular/material/list';
import { ITodo, TodoService } from '../../../services/todo/todo.service';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { TodoListItemComponent } from './todo-list-item/todo-list-item.component';

@Component({
  selector: 'todolist',
  standalone: true,
  imports: [
    MatListModule,
    CommonModule,
    FormsModule,
    TodoListItemComponent
  ],
  templateUrl: './todo-list.component.html',
  styleUrl: './todo-list.component.scss'
})
export class TodoListComponent implements OnInit {
  todos: ITodo[] = [];

  newTodoTitle = '';
  newTodoDescription = '';

  constructor(
    private todoService: TodoService,
  ) {}

  ngOnInit() {
    this.todoService.todos$.subscribe((todos: ITodo[]) => {
      this.todos = todos;
    });
  }

  addTodo() {
    this.todoService.addTodo(this.newTodoTitle, this.newTodoDescription);
    this.newTodoTitle = ''; // Clear the form after adding
    this.newTodoDescription = '';
  }

  removeTodo(index: number) {
    this.todoService.removeTodo(index);
  }
}
