export interface CubeController {
    init_solver(): void;
    execute_sequence_in_notation(s: string): void;
    print_state(): void;
    reset_cube_state(): void;
    find_solution(): string;
    get_state_corners(): any;
    get_state_edges(): any;
    generate_random_scramble(length: number): string;
    is_scramble_correct(s: string): boolean;
}

export interface CubeModule {
    CubeController: {
        new (): CubeController;
    };
}

export default function createModule(options?: any): Promise<CubeModule>;