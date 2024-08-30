import { Injectable } from '@angular/core';
import { ApiService } from '../api/api.service';
import { Observable } from 'rxjs';
import { GeoLocation, GeoResponse } from './geo.types';

const API_ENDPOINT: string = "https://geocoding-api.open-meteo.com/v1/search"

@Injectable({
  providedIn: 'root'
})
export class GeoService {

  constructor(
    private apiService: ApiService,
  ) { }

  getGCS(search: string): Observable<GeoResponse> {
    return this.apiService.get<GeoResponse>(API_ENDPOINT + `?name=${search}`);
  }
}
