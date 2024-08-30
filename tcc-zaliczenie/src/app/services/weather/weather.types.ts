export interface WeatherResponse {
    current: WeatherCurrent,
}

export interface WeatherCurrent {
    interval: number,
    rain: number,
    temperature_2m: number,
    time: string,
    is_day: number;
}