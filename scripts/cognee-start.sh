#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

mkdir -p "$PROJECT_DIR/.cognee-data"

echo "Starting Cognee..."
echo "  Frontend UI:  http://localhost:3000"
echo "  MCP (SSE):    http://localhost:8000/sse"
echo "  Backend API:  http://localhost:8010"
echo "  LLM:          Ollama @ host:11434"
echo ""

exec docker compose -f "$PROJECT_DIR/docker-compose.cognee.yml" up --build "$@"
