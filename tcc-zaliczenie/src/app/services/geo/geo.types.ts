export interface GCS {};

export interface GeoResponse {
    results: GeoLocation[];
}

export interface GeoLocation {
    latitude: number;
    longitude: number;
}