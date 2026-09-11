import {
    useEffect,
    useState,
} from "react";

import Buttons from "./components/Buttons";
import CommandEditor from "./components/CommandEditor";
import FileChooser from "./components/FileChooser";
import Header from "./components/Header";
import OutputPanel from "./components/OutputPanel";
import ServerStatus from "./components/ServerStatus";

import {
    analyzeCommands,
    checkServerStatus,
} from "./services/commandAPI";

import "./styles/app.css";

function App() {
    // conserva el nombre del archi
    const [fileName, setFileName] = useState("");

    // Guarda el comandos en editor
    const [commandText, setCommandText] = useState("");

    // Guarda los mensajes de output
    const [messages, setMessages] = useState<string[]>([]);

    const [isOnline, setIsOnline] = useState(false);

    useEffect(() => {
        const verifyServer = async (): Promise<void> => {
            const serverAvailable =
                await checkServerStatus();

            setIsOnline(serverAvailable);
        };

        verifyServer();
    }, []);

    //lee archivo y hace display en el eidto
    const handleFileSelected = async (
        event: React.ChangeEvent<HTMLInputElement>
    ): Promise<void> => {
        // Obtiene el inputFile
        const selectedFile =
            event.target.files?.[0];

        if (!selectedFile) {
            return;
        }

        const selectedFileName =
            selectedFile.name.toLowerCase();

        const validExtension =
            selectedFileName.endsWith(".txt") ||
            selectedFileName.endsWith(".smia");

        if (!validExtension) {
            setMessages([
                "Error: solo se permiten archivos con extensión .txt o .smia.",
            ]);

            return;
        }

        try {
            //lee archivo
            const content =
                await selectedFile.text();

            setFileName(selectedFile.name);

            //comandos en el editor
            setCommandText(content);

            //info mesage
            setMessages([
                `Archivo "${selectedFile.name}" cargado correctamente.`,
            ]);
        } catch {
            setMessages([
                "Error: no se pudo leer el archivo seleccionado.",
            ]);
        }
    };

    
    const handleAnalyze = async (): Promise<void> => {
        // Evita enviar un editor vacío.
        if (commandText.trim().length === 0) {
            return;
        }

        
        const serverAvailable =
            await checkServerStatus();

        setIsOnline(serverAvailable);

        if (!serverAvailable) {
            setMessages([
                "Error: no se pudo conectar con el backend.",
            ]);

            return;
        }

        try {
            
            const analysisResult =
                await analyzeCommands(commandText);

            
            setMessages(
                analysisResult.messages
            );
        } catch {
            
            setIsOnline(false);

            setMessages([
                "Error: ocurrió un problema al comunicarse con el backend.",
            ]);
        }
    };

    //lmpia el editor y sus resultados
    const handleClear = (): void => {
        setFileName("");
        setCommandText("");
        setMessages([]);
    };

    return (
        <div className="app-shell">
            <Header />

            <main className="app-main">
                <div className="toolbar">
                    <ServerStatus
                        isOnline={isOnline}
                    />
                </div>

                <FileChooser
                    fileName={fileName}
                    onFileSelect={handleFileSelected}
                />

                <CommandEditor
                    value={commandText}
                    onChange={setCommandText}
                />

                <Buttons
                    disabled={
                        commandText.trim().length === 0
                    }
                    onAnalyze={handleAnalyze}
                    onClear={handleClear}
                />

                <OutputPanel
                    messages={messages}
                />
            </main>

            <footer className="app-footer">
                Práctica 1 · Analizador léxico y sintáctico EXT2
            </footer>
        </div>
    );
}

export default App;