import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, catchError, throwError } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ApiService {

  constructor(
    private http: HttpClient,
  ) { }

  get<T>(endpoint: string): Observable<T> {
    return this.http.get<T>(endpoint)
      .pipe(
        catchError((error: any) => {
          console.error(`Error fetching data from ${endpoint}:`, error);
          return throwError('An error occured while fetching data.');
        })
      );
  }
}
