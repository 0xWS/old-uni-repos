import { Component, Input, OnInit } from '@angular/core';
import { WeatherService } from '../../../services/weather/weather.service';
import { WeatherResponse } from '../../../services/weather/weather.types';
import { MatCardModule } from '@angular/material/card';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { FaIconComponent, FontAwesomeModule } from '@fortawesome/angular-fontawesome';
import { faMoon, faSun } from '@fortawesome/free-solid-svg-icons';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'temperature-card',
  standalone: true,
  imports: [
    MatCardModule,
    MatProgressSpinnerModule,
    FontAwesomeModule,
    CommonModule
  ],
  providers: [ WeatherService ],
  templateUrl: './temperature.component.html',
  styleUrl: './temperature.component.scss'
})
export class TemperatureComponent implements OnInit {
  @Input() location: string = "";
  temperature: number = 0;
  isDay: boolean = true;

  //Font awesome
  faMoon = faMoon;
  faSun = faSun;

  loading: boolean = true;

  constructor(
    private weatherService: WeatherService,
  ) {}

  ngOnInit() {
    if(this.location) {
      this.weatherService.getCurrentWeather(this.location).subscribe((response: WeatherResponse) => {
        this.loading = false;
        this.temperature = response.current.temperature_2m;
        this.isDay = !!response.current.is_day;
      });
    }
  }

}
