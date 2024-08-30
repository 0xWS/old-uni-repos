import { Component, EventEmitter, Input, Output } from '@angular/core';

@Component({
  selector: 'todo-list-item',
  standalone: true,
  imports: [],
  templateUrl: './todo-list-item.component.html',
  styleUrl: './todo-list-item.component.scss'
})
export class TodoListItemComponent {
  @Input() index: number = -1;
  @Input() title: string = "";
  @Input() description?: string = "";
  @Input() weather?: string = "";
  @Output() removeTodoEmitter: EventEmitter<number> = new EventEmitter<number>();
  
  removeTodo(i: number) {
    this.removeTodoEmitter.emit(i);
  }
}
