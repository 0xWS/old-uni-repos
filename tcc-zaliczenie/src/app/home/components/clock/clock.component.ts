import { CommonModule } from '@angular/common';
import { Component, OnDestroy, OnInit } from '@angular/core';
import { MatCardModule } from '@angular/material/card';
import { MatProgressSpinner, MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { TimeService } from '../../../services/time/time.service';
import { Subject, takeUntil } from 'rxjs';

@Component({
  selector: 'clock-card',
  standalone: true,
  imports: [
    MatCardModule,
    MatProgressSpinnerModule,
    CommonModule,
  ],
  templateUrl: './clock.component.html',
  styleUrl: './clock.component.scss'
})
export class ClockComponent implements OnInit, OnDestroy {

  datetime: Date = new Date();
  datetimeString: String = "";

  loading: boolean = true;
  private destroy$ = new Subject<void>();

  constructor(
    private timeService: TimeService,
  ) { }

  ngOnInit() {
    this.updateTime();

    setInterval(() => {
      this.updateTime();
    }, 60 * 1000); // 60 seconds * 1000 milliseconds, refresh every minute
  }

  ngOnDestroy() {
    this.destroy$.next();
    this.destroy$.complete();
  }

  private updateTime() {
    this.timeService.getTime('Europe', 'Warsaw')
      .pipe(takeUntil(this.destroy$))
      .subscribe(result => {
        this.loading = false;
        this.datetime = new Date(result.datetime);
        this.datetimeString = this.buildDatetimeString(this.datetime);
      });
  }

  private buildDatetimeString(datetime: Date): string {
    const hours = datetime.getHours();
    const minutes = datetime.getMinutes();
    const formattedMinutes = minutes < 10 ? `0${minutes}` : minutes; 

    return `${hours}:${formattedMinutes}`
  }
}
