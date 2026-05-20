const std = @import("std");

// Estrutura do nó da pilha (Alocação Dinâmica)
const Node = struct {
    value: f64,
    next: ?*Node,
};

// Estrutura da Pilha
const Stack = struct {
    allocator: std.mem.Allocator,
    top: ?*Node = null,

    pub fn init(allocator: std.mem.Allocator) Stack {
        return Stack{ .allocator = allocator };
    }

    // Insere um elemento criando um nó dinamicamente
    pub fn push(self: *Stack, value: f64) !void {
        const node = try self.allocator.create(Node);
        node.value = value;
        node.next = self.top;
        self.top = node;
    }

    // Remove e retorna o elemento do topo, liberando a memória do nó
    pub fn pop(self: *Stack) ?f64 {
        const node = self.top or return null;
        self.top = node.next;
        const val = node.value;
        self.allocator.destroy(node);
        return val;
    }

    // Limpa qualquer resíduo da pilha para evitar vazamento de memória
    pub fn deinit(self: *Stack) void {
        while (self.pop()) |_| {}
    }
};

pub fn main(init: std.process.Init) !void {
    const allocator = init.gpa;
    const io = init.io;

    // Abre o arquivo de entrada ex11.z
    const file = std.Io.Dir.cwd().openFile(io, "ex11.z", .{}) catch |err| {
        std.debug.print("Erro ao abrir o arquivo 'ex11.z': {}\n", .{err});
        return;
    };
    defer file.close(io);

    // SOLUÇÃO: Criamos um buffer na stack para receber o texto do arquivo
    var buffer: [2048]u8 = undefined;
    const bytes_read = try file.read(io, &buffer);
    const content = buffer[0..bytes_read]; // Fatia contendo apenas o que foi lido

    var stack = Stack.init(allocator);
    defer stack.deinit();

    // Divide o conteúdo por espaços, tabulações ou quebras de linha
    var tokens = std.mem.tokenizeAny(u8, content, " \t\n\r");

    while (tokens.next()) |token| {
        // Verifica se o token é um operador básico
        if (std.mem.eql(u8, token, "+") or std.mem.eql(u8, token, "-") or 
            std.mem.eql(u8, token, "*") or std.mem.eql(u8, token, "/")) {
            
            // Desempilha os dois últimos valores
            const b = stack.pop() orelse {
                std.debug.print("Erro: Operandos insuficientes para o operador '{s}'.\n", .{token});
                return;
            };
            const a = stack.pop() orelse {
                std.debug.print("Erro: Operandos insuficientes para o operador '{s}'.\n", .{token});
                return;
            };

            const result = if (std.mem.eql(u8, token, "+")) a + b
            else if (std.mem.eql(u8, token, "-")) a - b
            else if (std.mem.eql(u8, token, "*")) a * b
            else if (std.mem.eql(u8, token, "/")) blk: {
                if (b == 0) {
                    std.debug.print("Erro: Divisão por zero detectada.\n", .{});
                    return;
                }
                break :blk a / b;
            } else unreachable;

            // Empilha o resultado da operação
            try stack.push(result);
        } else {
            // Se não for operador, tenta converter o texto para número (f64)
            const val = std.fmt.parseFloat(f64, token) catch |err| {
                std.debug.print("Erro: Token inválido encontrado '{s}' ({})\n", .{ token, err });
                return;
            };
            try stack.push(val);
        }
    }

    // Pega o resultado final da expressão
    const final_result = stack.pop() orelse {
        std.debug.print("Erro: Nenhuma expressão válida foi processada.\n", .{});
        return;
    };

    // Se sobrou algo na pilha, a expressão estava errada
    if (stack.top != null) {
        std.debug.print("Erro: Expressão mal formatada (sobraram elementos na pilha).\n", .{});
        return;
    }

    std.debug.print("Resultado Final: {d}\n", .{final_result});
}
