import { Injectable } from '@angular/core';
import { ApiService } from '../api/api.service';
import { Observable } from 'rxjs';
import { ITime } from './time.types';

const API_ENDPOINT: string = "https://worldtimeapi.org/api/";

@Injectable({
  providedIn: 'root'
})
export class TimeService {

  constructor(
    private apiService: ApiService
  ) { }

  getTimezones(): Observable<String[]> {
    return this.apiService.get<String[]>(API_ENDPOINT + 'timezone');
  }

  getLocations(area: String): Observable<String[]> {
    return this.apiService.get<String[]>(API_ENDPOINT + `timezone/${area}`)
  }

  getTime(area: String, location: String): Observable<ITime> {
    return this.apiService.get<ITime>(API_ENDPOINT + `timezone/${area}/${location}`);
  }
}
