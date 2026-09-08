interface OutputPanelProps {

    messages: string[]; //lista de outputs
}

function OutputPanel({ 
    messages,
}: OutputPanelProps) {
    return(
        <section className="output-panel-container">
            <div className="panel-header">
                <div>
                    <p className="panel-label">Salida de Comandos</p>
                    <h2 className="panel-title">Output</h2>
                </div>
            </div>

            <div 
            className="output-panel"
            aria-live="polite"
            >
                {messages.length === 0 ? (
                    <p className="output-panel-empty">Output de comandos...</p>
                ) : (
                    messages.map((message, index) => (
                        <p key={`${message}-${index}`} className="output-panel-line">
                            <span className="output-panel-symbol">
                                &gt;
                            </span>
                            {message}
                        </p>
                    ))
                )}
                </div>

        </section>

    );
}
export default OutputPanel;
