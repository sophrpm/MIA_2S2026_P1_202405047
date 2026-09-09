//Respuesta enviada a /api/analyze
export interface AnalysisResponse {
    success: boolean;
    messages: string[];
}

//Respuesta enviada a /api/health
export interface HealthResponse {
    success: boolean;
    message: string;
}