import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { ApiService } from '../api/api.service';
import { Observable, mergeMap } from 'rxjs';
import { WeatherResponse } from './weather.types';
import { GeoService } from '../geo/geo.service';
import { GeoLocation, GeoResponse } from '../geo/geo.types';

const API: string = "https://api.open-meteo.com/v1/forecast";

@Injectable({
  providedIn: 'root',
})
export class WeatherService {

  constructor(
    private apiService: ApiService,
    private geoService: GeoService,
  ) { }

  getCurrentWeather(location: string): Observable<WeatherResponse> {
    return this.geoService.getGCS(location)
      .pipe(
        mergeMap((response: GeoResponse) => {
          const location: GeoLocation = response.results[0];
          const coordinates: string = `latitude=${location.latitude}&longitude=${location.longitude}`
          const request: string = `${API}?${coordinates}&current=temperature_2m,is_day&forecast_days=1`;

          return this.apiService.get<WeatherResponse>(request);
        })
      );
  }
}
