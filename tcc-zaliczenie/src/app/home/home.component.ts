import { Component } from '@angular/core';
import { TemperatureComponent } from './components/temperature/temperature.component';
import { ClockComponent } from './components/clock/clock.component';
import { TodoListComponent } from './components/todo-list/todo-list.component';

@Component({
  selector: 'app-home',
  standalone: true,
  imports: [
    TemperatureComponent,
    ClockComponent,
    TodoListComponent,
  ],
  templateUrl: './home.component.html',
  styleUrl: './home.component.scss'
})
export class HomeComponent {

}
